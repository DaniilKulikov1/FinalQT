#ifndef PRIVATE_MESSAGE_H
#define PRIVATE_MESSAGE_H
#include <QString>
#include <QtSql/QSqlDatabase> //подключем библиотек для работы с базами данных и их подключения
#include <QtSql>// это тоже для работы с базами данных и подключения к ним, стандартные драйвера
#include <QSqlQuery>
/*
class Private_Message
{
public:
    Private_Message();
};*/

class Private_Message
{
private:
    QString privateRecepient;//кому
    QString privateSend;//кто
    QString privateText;//само сообщение



public:
    Private_Message();
    Private_Message(const QString& recepient, const QString& send, const QString text):privateRecepient(recepient), privateSend(send), privateText(text)
    {}

    QString Zapros_for_SQL; //это будет команда для SQL
    QString Zapros_for_SQL2; //для своих ЛС
    QString privateRecepient_p1;//кому
    QString privateSend_p1;//кто
    QString privateText_p1;//само сообщение



    const QString& getPrivateRecepient() const;
    const QString& getPrivateSend() const;
    const QString& getPrivateText() const;

//INSERT INTO MessegQT (WhyWrite, ForWrite, Message) VALUES ('Admin', 'All','Hello world');//тут будет другая функция
    void privateMessege_in_SQL();
    void SelfprivateMessege_in_SQL();

};
#endif // PRIVATE_MESSAGE_H
