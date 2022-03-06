#include "headlines.hpp"

headlines::headlines() {
    this->contentType = "";
    this->contentEncoding = "";
    this->contentLenght = "";
    intLenght = 0;
}

headlines::~headlines() {}


void            headlines::searchKey() {
    RequestParser requestParser; //todo: Maybe I need throw exception??

    if (requestParser.request.head.find("Accept-Encoding") != requestParser.request.head.end())
        contentEncoding = requestParser.request.head["Accept-Encoding"] + "/r/n"; // really?
    if (!requestParser.request.body.empty()) {// if the request has body
        intLenght = strlen(requestParser.request.body.c_str()); //todo: How I have to count lenght?
        std::stringstream ss;
        ss << intLenght;
        contentLenght = ss.str();
    }
    if (requestParser.request.head.find("Accept") != requestParser.request.head.end())
        contentType = requestParser.request.head["Accept"] + "/r/n";

    //
    // todo: server: gulu gulu
}

std::string     headlines::getType() {
    return (this->contentType);
}

std::string     headlines::getEncoding() {
    return (this->contentEncoding);
}

std::string     headlines::getLenght() {
    return (this->contentLenght);
}