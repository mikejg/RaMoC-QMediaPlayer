#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Log::info("Starte RamocServer");
    ui->setupUi(this);
    setStyleSheet("QMainWindow {background: 'silver';}");

    label_ChannelIcon = new QLabel(this);
    player            = new M_OMXPlayer(this);
    insertMovies      = new InsertMovies(this);
    process_TrailerDL = new QProcess(this);
    database          = new DataBase();
    server            = new Server(player, database, this);
    lastFm            = new M_LastFm(this);

    connect(database, SIGNAL(sig_PlayedSet()),                server, SIGNAL(sig_PlayedSet()));
    connect(database, SIGNAL(sig_SendUnsortedFiles(QString)), server, SIGNAL(sig_SendUnsortedFiles(QString)));

    connect(server, SIGNAL(sig_InsertMovies()),          this,     SLOT(handleInsertMovies()));
    //connect(server, SIGNAL(sig_SetPlayed(QString)),      database, SLOT(onSetPlayed(QString)));
    connect(server, SIGNAL(sig_GetUnsortedFiles()),      database, SLOT(onGetUnsortedFiles()));
    connect(server, SIGNAL(sig_NewChannelIcon(QPixmap)), this,     SLOT(onNewChannelIcon(QPixmap)));
    connect(server, SIGNAL(sig_InsertMovie(QString, QString)), this, SLOT(onInsertMovie(QString, QString)));
    
    connect(insertMovies, SIGNAL(sig_NewInfo(QString)),    this, SLOT(handleNewInfo(QString)));
    connect(insertMovies, SIGNAL(sig_NewTrailer(QString)), this, SLOT(handleNewTrailer(QString)));
    connect(insertMovies, SIGNAL(finished()),              this, SLOT(handleInsertMovies_Finished()));

    connect(player, SIGNAL(sig_SetPlayed(QString)),      database, SLOT(onSetPlayed(QString)));
    connect(player, SIGNAL(sig_PlayingTrack(Track)),      this, SLOT(onPlayingTrack(Track)));
    connect(player, SIGNAL(sig_PlayingMovie()),           this, SLOT(onPlayingMovie()));

    connect(process_TrailerDL, SIGNAL(finished (int, QProcess::ExitStatus)),
            this, SLOT(trailer_Download_Finished(int, QProcess::ExitStatus)));

    connect(lastFm, SIGNAL(new_Artist_Pixmap(QPixmap)), this, SLOT(onNewArtistPixmap(QPixmap)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDesktop(QDesktopWidget *d)
{
    desktop = d;
    QRect rec = desktop->availableGeometry(this);
    setGeometry(0,0,desktop->width(), desktop->height());
    pixmap_Main = QPixmap(":/Bilder/Wallpaper");
    pixmap_Main = pixmap_Main.scaled(rec.width(),rec.height());
    ui->label->setPixmap(pixmap_Main);
    ui->label->setGeometry(0,0,rec.width(), rec.height());
    ui->labelDebug->setGeometry(rec.width()/2 - 150,
                                rec.height()*0.66,
                                300,30);
    ui->labelDebug->setText("DEBUG");

    ui->widget_Music->setGeometry(0,0,rec.width(),rec.height());
    pixmap_Music = QPixmap(":/Bilder/wallpaper_Music");
    pixmap_Music = pixmap_Music.scaled(rec.width(),rec.height());

    ui->label_Title->setGeometry(0,
                                 (int)(rec.height() - (rec.height() * 0.09)),
                                 rec.width(),
                                 (int)(rec.height() * 0.09));
    ui->label_Artist->setGeometry(0,
                                 (int)(rec.height() - (rec.height() * 0.09) * 2 - 10 ),
                                 rec.width() - 310,
                                 (int)(rec.height() * 0.09));

    ui->label_ArtistPic->setGeometry(rec.width() - 310,
                                 (int)(rec.height() - (rec.height() * 0.09) - 310 ),
                                 300,
                                 300);


    ui->widget_Music->hide();

    label_ChannelIcon->setGeometry(rec.width()/2 - 480,
                                   rec.height()/2 - 270,960,540);
    //label_ChannelIcon->setScaledContents(true);
    label_ChannelIcon->setAlignment(Qt::AlignCenter);
    label_ChannelIcon->hide();

    //IP suchen und anzeigen
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    QString ipAddress;

    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    //Wenn nichts gefunden wurde dann nimm localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    ui->labelDebug->setText(ipAddress);

    QTimer::singleShot(30000, ui->labelDebug, SLOT(hide()));
}

void MainWindow::handleInsertMovies()
{
  if(!insertMovies->isRunning())
    insertMovies->start();
}

void MainWindow::handleNewInfo(QString str)
{
  ui->labelDebug->show();
  ui->labelDebug->setText(str);
}

void MainWindow::handleNewTrailer(QString str)
{
  stringList_Trailer << str;
}

void MainWindow::handleInsertMovies_Finished()
{
  trailer_Download_Finished(0, QProcess::NormalExit);
}

void MainWindow::trailer_Download_Finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    static QString string_Trailer = QString("");
    QString string_Link;

    //Der letzte Trailer muss noch verlinkt werden
    if(string_Trailer != QString(""))
    {
      qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Verlinke Trailer: " << string_Trailer;
      string_Link = "ln -s /media/ramoc/Trailer/" + string_Trailer + ".mp4 " + 
                          "/var/www/html/Trailer/" + string_Trailer;
      system(string_Link.toLatin1().data());
    }

    if(!stringList_Trailer.isEmpty())
    {
      string_Trailer = stringList_Trailer.takeFirst();
      string_Link = "ln -s /media/ramoc/Trailer/" + string_Trailer + ".mp4 " + 
                        "/var/www/html/Trailer/" + string_Trailer;
      QFileInfo fileInfoTrailer("/media/ramoc/Trailer/" + string_Trailer + ".mp4");
      if(fileInfoTrailer.exists())
      {
        qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Trailer ist schon vorhanden";
        trailer_Download_Finished(0, QProcess::NormalExit);
        return;
      }

      qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Start Trailerdownlaod " << string_Trailer;
      QString execString = "youtube-dl -f 18 -o /media/ramoc/Trailer/" + string_Trailer + ".mp4 "
                         " http://www.youtube.com/watch?v=" + string_Trailer;
      process_TrailerDL->start(execString);
    }
    else
    {
      qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Kein neuer Trailer vorhanden";
      string_Trailer = QString("");
    }
}

void MainWindow::onNewChannelIcon(QPixmap pixmap)
{
  label_ChannelIcon->setPixmap(pixmap.scaled(960,540,Qt::KeepAspectRatio));
  label_ChannelIcon->show();
  ui->label->hide();
  ui->widget_Music->hide();
  QTimer::singleShot(10000, label_ChannelIcon, SLOT(hide()));
  QTimer::singleShot(10000, ui->label, SLOT(show()));
}

void MainWindow::onInsertMovie(QString file_path, QString title)
{
  QFileInfo info(file_path);
  QFile file(file_path);
  QDir dir = info.dir();
  QString tmp = dir.absolutePath() + "/" + title + "." + info.suffix();
  file.rename(tmp);
  if(!insertMovies->isRunning())
    insertMovies->start();
}

void MainWindow::onPlayingTrack(Track track)
{
    ui->label->setPixmap(pixmap_Music);

  ui->label_Title->setText(track.title);
  ui->label_Artist->setText(track.artist);
  ui->widget_Music->show();

  lastFm->start_Search_Artist_Image(track.artist);
}

void MainWindow::onNewArtistPixmap(QPixmap pixmap)
{
    QPixmap pix(310,310);
    pix.fill(QColor(255,0,0,0));
    QPainter p(&pix);
    QPainterPath path;
    path.addEllipse(5,5,300,300);
    p.setClipPath(path);
    p.drawPixmap(5,5,pixmap);
    //pix = pix.scaled(300,300);
    ui->label_ArtistPic->setPixmap(pix);
}

void MainWindow::onPlayingMovie()
{
  ui->label->setPixmap(pixmap_Main);
  ui->widget_Music->hide();
}
