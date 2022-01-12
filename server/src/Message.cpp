#include "Message.h"

Message::Message(int id, string autor, string tekst)
{
    author = autor;
    text = tekst;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, 20, "%d/%m/%y, %H:%M",timeinfo);
}
