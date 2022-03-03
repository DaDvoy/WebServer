#include "headlines.hpp"

void            headlines::searchKey() {
    RequestParser requestParser;

    contentType = requestParser.request.head["Accept"] + "/r/n";
    contentEncoding = requestParser.request.head["Accept-encoding"] + "/r/n"
    if (contentLenght = requestParser.request.body) // if the request has body
        intLenght = contentLenght.size();
    mb_

}