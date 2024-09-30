#include "private_message.h"

//Private_Message::Private_Message() {}
Private_Message::Private_Message()
{
    QString privateRecepient=" ";
    QString privateSend;//кто
    QString privateText;//само сообщение
}



const QString& Private_Message::getPrivateRecepient() const
{return privateRecepient;}


const QString& Private_Message::getPrivateSend() const
{return privateSend;}

const QString& Private_Message::getPrivateText() const
{return privateText;}


void Private_Message::privateMessege_in_SQL()
{
//тут изменить //изменено

 //INSERT INTO PrivateMesseges (User, Private_Messeg) VALUES ('Максим', 'Ты зеленков?');
//Ниже дописать отправителя и его текст
//Zapros_for_SQL="INSERT INTO PrivateMesseges (User, Private_Messeg) VALUES ('Аня', 'Ты красивая?');";

 Zapros_for_SQL="INSERT INTO PrivateMesseges (User, Private_Messeg) VALUES ('" + privateRecepient_p1 + "','" + privateSend_p1 + ": "
                         + privateText_p1 + "');";

}


 void Private_Message:: SelfprivateMessege_in_SQL()
{
    //это чтобы видеть свои ЛС

  Zapros_for_SQL2="INSERT INTO PrivateMesseges (User, Private_Messeg) VALUES ('" + privateSend_p1 + "','" + privateSend_p1 + ": "
                     + privateText_p1 + "');";


}


//таблица для приватных сообщений
/*CREATE TABLE PrivateMesseges (
    id INT AUTO_INCREMENT PRIMARY KEY,
    User VARCHAR(255) NOT NULL,
    Private_Messeg TEXT NOT NULL
);*/



