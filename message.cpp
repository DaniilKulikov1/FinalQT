#include "message.h"

Message::Message()
{
    recepient_p=" ";
    send_p=" ";
    text_p=" ";
}



const QString& Message::getRecepient() const
{return recepient_p;}


const QString& Message::getSend() const
{return send_p;}

const QString& Message::getText() const
{return text_p;}

//INSERT INTO MessegQT (Message) VALUES ('Ваше сообщение здесь');
//INSERT INTO MessegQT Message VALUES (''Hello world');
void Message::Messege_in_SQL()
{
//тут изменить
    Zapros_for_SQL="INSERT INTO MessegQT (Message) VALUES ('" + send_p1 + recepient_p1 + text_p1 + "');";
    //вот мы сделали строку для передачи в базу данных
    //тут  пишем отправку в таблицу как в функции с юзерам

}
