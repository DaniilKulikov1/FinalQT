#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase> //подключем библиотек для работы с базами данных и их подключения
#include <QtSql>// это тоже для работы с базами данных и подключения к ним, стандартные драйвера
#include <QVector>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase db; //этот обьект создадим, чтобы подключаться к нашему MySQL
    bool CheckLogin; //эту переменную мы создадим, чтобы при её активации становилась активной функция показа сообщений
    //или других пользователей

private:
    Ui::MainWindow *ui;

private slots:

void privetstvieUsera();//этой функцией поприветствуем пользователя, расскажем о создателе - мне,
//и покажем дракона, невзирая на то нажал он кнопки или нет

void click_Close_Chat();//этой кнопкой будем сразу закрывать окошки чата
void Connection(); //этой подключаем соединение с базой данных как только пользователь вошёл
void click_Registration();//' слот регистрации этим слотом будет добавлять новых пользователей в чат,
//а точнее в таблицу БД UsersQT

void Enter_in_Chat();//после этой функции увидем пользователей, и будем писать смс и читать
void Show_Users();//этот метод чтобы вывести список всех зарегестрированных пользователей, его добавим в метод входа в чат
void Unlogin();//функция - покинуть свой логин
void Send_Messege(); //функция отправки сообщения
void Show_Messege();//тут покажем все сообщения из базы данных
void Send_privateMessege(); //приватная оправка сообщений
void showPrivate_Messeges();//показ приватных сообщений
void BanUser();//эта функция не даст юзеру войти в чат, и соответственно читать и писать смс

};
#endif // MAINWINDOW_H

//нужно чтобы при входе класс юзер запоминал в обьекте кто в него вошёл
