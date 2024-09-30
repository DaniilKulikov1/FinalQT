#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dragon.h"
#include "user.h"
#include "message.h"
#include "private_message.h"

User userLogger;//делаем обьект того, кто вошёл, туда запишем имя из БД

 //ВЫВОД СООБЩЕЙНИЙ УДАЛСЯ! И ОТПРАВКА СООБЩЕНИЙ УДАЛАСЬ!
//Нужно чтобы сообщение выводилось после набора юзером//это я тоже сделал
//теперь нужен класс приватных сообщений и ещё одна таблица в базах данных - есть
//нужно переделать класс приват месседж сделав его из месседж - есть
//нужно сделать слот приватной отправки и его протатип - сделано
//когда это получится - сделать приватный показ
//нужен приватный дисплей - сделано
//нужно показать приватное сообщение

/*CREATE TABLE PrivateMesseges (
    id INT AUTO_INCREMENT PRIMARY KEY,
    User VARCHAR(255) NOT NULL,
    Private_Messeg TEXT NOT NULL
);*/



void MainWindow::privetstvieUsera()
{   //сюда поместим вывод рисунка дракона на экран и пару сообщений
    //сюда поместим вывод рисунка дракона на экран и пару сообщений
    Dragon dragon;//cоздадим обьект для приветствия пользователя
    ui->Public_Display->append(dragon.Hello); //на главный экран выведем слова привет юзер из класса
    ui->Public_Display->append(dragon.Hello1);//ниже напишем, что его создал я - Даниил Куликов
    ui->Public_Display->append(dragon.Yasher); //Покажем дракона которого я рисовал весь год
    ui->Public_Display->append(" ");//Выведем пробел
    ui->Public_Display->append(" ");//Выведем ещё один пробел
    //Теперь перенесём все в ту функцию - главного окна ниже
    //функция выполнена, редакция не требуется
}


void MainWindow::click_Close_Chat()
{
    //этой функцией сразу вырубаем чат
    this->close();
    //сейчас нужно написать связку с главным окном
    //функция выполнена, редакция не требуется
}


void MainWindow::Show_Users()
{//это функция будет выводить список пользователей в виджет
    //тут будем делать вывод юзеров из БД
    if(CheckLogin)
    {
        //qDebug()<<"Тут будет действие!";
        QString Zapros="SELECT UserQT FROM UsersQT";
        QSqlQuery query(db);
        if (query.exec(Zapros))
        {

            ui->List_Users->clear();

            while (query.next())
            {
                QString login = query.value(0).toString();
                ui->List_Users->append(login);
            }

        }
        else
        {
            ui->List_Users->append("Вы не видите других пользователей.");
            ui->List_Users->append("Потому, что не вошли.");
        }

    }

}



void MainWindow::Connection()
{
    //тут будем сразу подключатьсяк нашей базе данных
    db = QSqlDatabase::addDatabase("QODBC"); //создаём обьект класса база данных сикьюэль и зафолняем его функцией  в которую передали строку
    //с название драйвера
    db.setDatabaseName("Driver={MySQL ODBC 9.0 Unicode Driver};DATABASE=for_words;");
    //у обьекта вызываем установку имени бд, и передаём строкой название драйвера и Нашей базы данных (у меня она называетсяfor_words
    db.setUserName("root");
    //вызываем через обьект поле пользователь и передаём строкой его имя
    db.setPassword("MayAzot777");
    //вызываем поле пароль и передаём пароль от нашей учетно записи

    if (!db.open())
    {
        qDebug() << db.lastError().text();
        //если функци открытия не сработала - вывлжим ошибку
    }
    else

    {
        qDebug()<<"Cоединение с базой данных MySQL подключено!";
        //если сработало пишем подключено
    }
    //сразу переносим эту функцию в главное окно
    //функция выполнена, редакция не требуется
}



void MainWindow::click_Registration()
{
    QString Log;//логин юзера
    QString Pas;//пароль юзера

    Log=ui->Login_R->text();//получаем логин из окошка логина
    Pas=ui->Password->text();//получаем из окошка пароль

    if(Log.isEmpty() || Pas.isEmpty())
    {//часть первая - проверим, ввел ли наш пользователь логин и пароль
        ui->Public_Display->append("Вы не ввели логин или пароль"); //Пишем ему об этом
        return;
    }

    //сделаем строку для передачи логина в базу данных, чтобы проверить есть ли он
    //мы передаём туда команду "SELECT COUNT(*) FROM UsersQT WHERE UserQT = 'Максим';"
    QString Zapros1="SELECT COUNT(*) FROM UsersQT WHERE UserQT = '";
    QString Zapros2="';";
    QString RezultZapros=Zapros1 + Log + Zapros2;

    QSqlQuery query(db);//делаем обьект для обмена с бд, и пишеи туда обьект базы данных

    if (query.exec(RezultZapros))
    { //если такая строка имеет значение тру
        if (query.next())
        { // Переходим к первой (и единственной) строке результата
            int count = query.value(0).toInt(); // Получаем значение из первой колонки

            if (count > 0)
            {
                ui->Public_Display->append("Такой пользователь есть, придумайте новый логин");
            }

            else
            {
                //передаём логин и пароль в бд
                //"INSERT INTO UsersQT (UserQT, PasswordQT) VALUES ('Максим', 'ьзцау74646');"

                QString Com1="INSERT INTO UsersQT (UserQT, PasswordQT) VALUES ('";
                QString Com2="', '";
                QString Com3="');";
                QString ResultUser=Com1 + Log + Com2 + Pas + Com3;
                query.exec(ResultUser); //передаём туда пользователя

                ui->Public_Display->append("Вы успешно зарегестрировались и можете:");
                ui->Public_Display->append(" - Видеть тех пользователей кто зарегистрирован");
                ui->Public_Display->append(" - Для входа введите логин и пароль и войдите");


            }
        }

        else
        {
            ui->Public_Display->append("Ошибка выполнения запроса");
        }
    }

    else
    {
        ui->Public_Display->append("Ошибка выполнения запроса");
    }

//функция завершена, пока редакции не требуется

}





void MainWindow::Enter_in_Chat()
{
    //тут сделаем вывод пользователей в на экран
    QString Log1;//логин юзера
    QString Pas1;//пароль юзера

    Log1=ui->Login_R->text();//получаем логин из окошка логина
    Pas1=ui->Password->text();//получаем из окошка пароль

    userLogger.setName(Log1); // вобьект класса юзер передано имя из базы данных, будем брать имя для сообщений отсюда. //Тут нет сеттера!
    userLogger.getPassword()=Pas1;

    qDebug()<<"К нам вошёл:"<< userLogger.getName();

//CheckLogin=true;//cтавим отметку, что да, пользователь вошёл и к этой переменной привяжем другие слоты

    if(Log1.isEmpty() || Pas1.isEmpty())
    {//часть первая - проверим, ввел ли наш пользователь логин и пароль
        ui->Public_Display->append("Вы не ввели логин или пароль"); //Пишем ему об этом
        return;//только ввёл
    }

//Cделаем проверку логина и пароля на основе строки SQL
//SELECT COUNT(*) FROM UsersQT WHERE UserQT ='Максим' AND PasswordQT='777';

    QString COM1="SELECT COUNT(*) FROM UsersQT WHERE UserQT ='";
    QString COM2="' AND PasswordQT='";
    QString COM3="';";
    QString ResultUserEnter=COM1 + Log1 + COM2 + Pas1 + COM3;
    qDebug()<<ResultUserEnter;

    QSqlQuery query(db);//делаем инициализацию этого обьекта как в коде регистрации

     if (query.exec(ResultUserEnter))
    {
        if (query.next())
        { // Переходим к первой (и единственной) строке результата
            int count = query.value(0).toInt(); // Получаем значение из первой колонки

            if (count > 0)
            {

                QString hi=userLogger.getName() + ", поздравляем, вы успешно вошли в аккаунт!";
                CheckLogin=true;//тут ставим выключатель на вкл, для функций показа и смс // при унлоге - ставим выкл.
                ui->Public_Display->append(hi);
                ui->Public_Display->append("Вы можете видеть список всех пользователей чата.");
                ui->Public_Display->append("Вы можете читать сообщения.");
                ui->Public_Display->append("Вы можете писать сообщения.");
                //теперь сделаем привязку к кнопке

                ui->Login_R->clear();//чистим окно входа
                ui->Password->clear();//чистим окно пароля

                Show_Users();
                Show_Messege();
                showPrivate_Messeges();
            }

        }
    }

}



void MainWindow::Unlogin()
{
    ui->Public_Display->clear();
  //  ui->Private_Display->clear(); //это описать потом
    ui->Public_Display->append("Вы покинули аккаунт.");
    ui->Public_Display->append("Вы не можете отправлять и читать сообщения.");
    ui->Public_Display->append("Для того чтобы войти в аккаунт наберите свой логин и пароль и войдите.");
    ui->List_Users->clear(); //cписок людей очищен
    ui->Private_Display->clear(); // cписок ЛС очищен
    //нужно сделать регчат фолс
    CheckLogin=false;
}







void MainWindow::Send_Messege()  //функция отправки сообщения
{
    QString Soobshenie;
    Soobshenie=ui->Messedge_Edit->text();//приняли смс из окошка

    QString Sender=userLogger.getName() + " :";//записали имя отправителя и поставили двоеточие

    QString For=". Сообщение всем: ";


    Message Sms(For, Sender, Soobshenie); //обьект, сюда передаём данные через конструктор

    Sms.recepient_p1=Sms.getRecepient();
    Sms.send_p1=userLogger.getName();
    Sms.text_p1=Sms.getText();

    Sms.Messege_in_SQL();//собираем запрос для MySQL
    QSqlQuery query(db);//делаем обьект для обмена с бд, и пишем туда обьект базы данных

    qDebug()<<Sms.Zapros_for_SQL;
    query.exec(Sms.Zapros_for_SQL);//передали в бд сообщение


    ui->Messedge_Edit->clear();//чистим написанное поле сообщения


    QString ResultPrivate=Sms.send_p1 + For + " "  +Soobshenie;
    ui->Public_Display->append(ResultPrivate);
}



//теперь нужна функция показа сообщений из базы данных
void MainWindow::Show_Messege()
{    //тут будет код выводящий колонку с сообщением


    //тут будет сообщение, точнее его показ
    if(CheckLogin)
    {
        //qDebug()<<"Тут будет действие!";
        QString Zapros="SELECT Message FROM MessegQT;";
        QSqlQuery query(db);
        if (query.exec(Zapros))
        {

            while (query.next())
            {
              QString SoobshenieBD = query.value(0).toString();
               ui->Public_Display->append(SoobshenieBD);

            }

        }
        else
        {
            ui->Public_Display->append("Вы не можете читать публичные смс.");

        }

    }
}






void MainWindow::Send_privateMessege()  //ЕГО ПРАВЛЮ над ним работаю
{
    //тут сделать реализацию отправуи приватного сообщения
    QString SoobsheniePrivat;
    SoobsheniePrivat=ui->privateMessedge_Edit_2->text();//приняли приватное смс из окошка
    QString SenderPrivat=userLogger.getName(); //мы приняли имя потправителя

    QString Persona=ui->Personal_User->text();//мы приняли имя адресата

    Private_Message PrivateSms(Persona, SenderPrivat, SoobsheniePrivat);//мы передали в класс приватных сообщений получателя, отправителя и текст


    PrivateSms.privateRecepient_p1=PrivateSms.getPrivateRecepient(); //отредактированно
    PrivateSms.privateSend_p1=PrivateSms.getPrivateSend();
    PrivateSms.privateText_p1=PrivateSms.getPrivateText();

    PrivateSms.privateMessege_in_SQL(); //cобираем сообщение для MySQL // теперь оно собрано
    qDebug()<<PrivateSms.Zapros_for_SQL;
    QSqlQuery query(db);//подключаемся к бд
    qDebug()<<PrivateSms.Zapros_for_SQL;//тестим
    query.exec(PrivateSms.Zapros_for_SQL);//передали в бд сообщени, в смысле код для MySQL для занесения в таблицу
    ui->Personal_User->clear();//чистим после отправки юзеру его имя в окошке
    ui->privateMessedge_Edit_2->clear();//чистим сообщение в окошке после того, как отправили юзеру смс

    //теперь продублируем это сообщение в своё окно, чтобы видеть, чем мы ответили на ЛС
    PrivateSms.SelfprivateMessege_in_SQL();//делаем копию для своего обзора
    query.exec(PrivateSms.Zapros_for_SQL2);//и передаём в MySQL
    ui->Private_Display->append(PrivateSms.privateSend_p1 + ". " + "Для: " + PrivateSms.privateRecepient_p1 + ". Сообщение: " + PrivateSms.privateText_p1);//выводим на экран в лс себе

}



void MainWindow::showPrivate_Messeges()
{
//тут реализовать код показа личных сообщений
// SELECT Private_Messeg FROM PrivateMesseges WHERE USER='Грег'; //основа запроса
    QString Privat_Messseg_For_User="SELECT Private_Messeg FROM PrivateMesseges WHERE USER='" + userLogger.getName() + "';";
//вот наш запрос для бд теперь передадим его туда
       QSqlQuery query(db);
    qDebug()<<Privat_Messseg_For_User;
  //  query.exec(Privat_Messseg_For_User);

    if (query.exec(Privat_Messseg_For_User))
    {
        // Получаем виджет, в котором будем отображать сообщения
       // QListWidget* privateDisplayWidget = ui->privateDisplayWidget;

        // Очищаем виджет, чтобы не было дублирования
      //  privateDisplayWidget->clear();

        // Проходим по результатам запроса и добавляем каждое сообщение в виджет
        while (query.next())
        {
            QString message = query.value(0).toString();
            //privateDisplayWidget->addItem(message);
            ui->Private_Display->append(message);
        }
    }
    else
    {
        // Если запрос завершился неудачно, выводим сообщение об ошибке
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
    }


}



void MainWindow::BanUser()
{
    //тут будем банить юзера так, чтобы он не зашёл
    //на основе будем банить UPDATE usersqt SET PasswordQT='708914697415693295' WHERE UserQT='Максим';
     QString Ban_Persona=ui->Personal_User->text();//мы приняли имя адресата
     //Теперь соберём код для смены пароля юзеру


     QString Ban_Password=ui->ban_Password->text();

     QString OneCommand="UPDATE usersqt SET PasswordQT='";
     QString SecondCommand="' WHERE UserQT='";
     QString ThridCommand="';";

     QString Ban=OneCommand + Ban_Password + SecondCommand + Ban_Persona + ThridCommand;//передали команду смены пароля в МySQL
     QSqlQuery query(db);//подключаемся к бд
     query.exec(Ban);//передаём этот запрос в MySQL
     ui->Personal_User->clear(); //чистим окошко с персональным юзером

     //-------сообщение о бане покажем всем
     QString Soobshenie="Пользователь "+Ban_Persona + " Забанен и не сможет войти в чат";
     QString Sender=userLogger.getName() + " :";//записали имя отправителя и поставили двоеточие

     QString For=". Сообщение всем: ";


     Message Sms(For, Sender, Soobshenie); //обьект, сюда передаём данные через конструктор

     Sms.recepient_p1=Sms.getRecepient();
     Sms.send_p1=userLogger.getName();
     Sms.text_p1=Sms.getText();

     Sms.Messege_in_SQL();//собираем запрос для MySQL // там всем будет написано что юзер забанен
     query.exec(Sms.Zapros_for_SQL);//передали в бд сообщение

    ui->Public_Display->append("Пользователь "+Ban_Persona + " Забанен и не сможет войти в чат");

}




MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    privetstvieUsera();//здороваемся с юзером и показываем дракона
    Connection();//сразу подключаем соединение с MySQL
    connect(ui->pushButton_Close, SIGNAL(clicked()), this, SLOT(click_Close_Chat()) );//этим слотом закрываем чат. Совсем.
    connect(ui->pushButton_Registration, SIGNAL(clicked()), this, SLOT(click_Registration()) );//этим слотом регистрируем пользователя
    connect(ui->pushButton_Enter, SIGNAL(clicked()), this, SLOT(Enter_in_Chat()) );//тут пишем юзеру вы вошли и активируем другие функции
    connect(ui->pushButton_Away, SIGNAL(clicked()), this, SLOT(Unlogin()));//выход юзера из аккаунта
    connect(ui->pushButton_SendMessege, SIGNAL(clicked()), this, SLOT(Send_Messege()));//это наша функция отправки сообщения в базу данных
    connect(ui->pushButton_Send_Private_Messege, SIGNAL(clicked()), this, SLOT(Send_privateMessege()));//послыпем приватное сообщение
    connect(ui->pushButton_Ban_User, SIGNAL(clicked()), this, SLOT(BanUser()));
}


MainWindow::~MainWindow()
{
    delete ui;
}
