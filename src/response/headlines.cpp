#include "headlines.hpp"

void            headlines::searchKey() {
    RequestParser requestParser;

    if (requestParser.request.head["Accept-Encoding"] != requestParser.request.head.end())
        contentEncoding = requestParser.request.head["Accept-Encoding"] + "/r/n" // really?
    if (requestParser.request.body != requestParser.request.body.end()) {// if the request has body
        contentLenght = requestParser.request.body;
        intLenght.sizeof(contentLenght); //todo: How I have to count lenght?
        std::stringstream ss;
        ss << intLenght;
        lenght
    }
    contentType = requestParser.request.head["Accept"] + "/r/n";

    //
    // todo: server: gulu gulu
}