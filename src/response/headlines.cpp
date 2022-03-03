#include "headlines.hpp"

void            headlines::searchKey() {
    RequestParser requestParser;

    if (requestParser.request.head["Accept-Encoding"] != requestParser.request.head.end())
        contentEncoding = requestParser.request.head["Accept-Encoding"] + "/r/n" // really?
    if (contentLenght = requestParser.request.body) // if the request has body
        intLenght = contentLenght.size(); //todo: How I need to count lenght?
    contentType = requestParser.request.head["Accept"] + "/r/n";


    //
    // todo: server: gulu gulu
}