#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QtSql/QSqlDatabase> //подключем библиотек для работы с базами данных и их подключения
#include <QtSql>// это тоже для работы с базами данных и подключения к ним, стандартные драйвера
#include <QSqlQuery>

class Message
{
private:
    QString recepient_p;//кому
    QString send_p;//кто
    QString text_p;//само сообщение



public:
    Message();
    Message(const QString& recepient, const QString& send, const QString text):recepient_p(recepient), send_p(send), text_p(text)
    {}

    QString Zapros_for_SQL; //это будет команда для SQL
    QString recepient_p1;//кому
    QString send_p1;//кто
    QString text_p1;//само сообщение



    const QString& getRecepient() const;
    const QString& getSend() const;
    const QString& getText() const;

//INSERT INTO MessegQT (WhyWrite, ForWrite, Message) VALUES ('Admin', 'All','Hello world');
    void Messege_in_SQL();

};

#endif // MESSAGE_H
