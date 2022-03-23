#include "Headlines.hpp"

Headlines::Headlines() {
    this->contentType = "";
    this->contentEncoding = "";
    this->contentLenght = "";
    this->contentRange = "";
    this->expires = "";
    this->typeEncoding = "";
    this->transferEncoding = "";
    this->chunked = "";
    intLenght = 0;
}

Headlines::~Headlines() {}


std::string     Headlines::sortData(std::string tmp) {
    int         pos;
    std::string final;
    std::string day, month, number, time, year;
    std::string probel = " ";

    tmp.append(" ");
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        day = tmp.substr(0, pos);
        tmp.erase(0, day.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        month = tmp.substr(0, pos);
        tmp.erase(0, month.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        number = tmp.substr(0, pos);
        tmp.erase(0, number.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        time = tmp.substr(0, pos);
        tmp.erase(0, time.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        year = tmp.substr(0, pos - 1);
        tmp.erase(0, year.size());
    }
    final = day + ", " + number + " " + month + " " + year + " " + time + " GMT";
    return (final);
}

void            Headlines::expiresTime() {
    time_t now = time(0);
    std::string tmp;

    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    tmp = dt;
    expires = sortData(tmp);
}


void            Headlines::processingRange() {
    std::map<std::string, std::string>::iterator it = req.head.begin();
    std::string tmp;
    int pos;

    it = req.head.find("Accept-Ranges");
    if (it->second != "none") {
        contentRange = req.head["Accept-Ranges"];
        pos = contentRange.find("bytes");
        tmp = contentRange.substr(pos);
        if (std::string::npos != tmp.find("/")) {
            pos = tmp.find("/");
            tmp.erase(pos);
            if (tmp.find_first_not_of("1234567890"))
                _status.RangeNotSatisfiable();
        }
    }
}

void            Headlines::processingChunk(std::string path) {
    std::string tmp;
    std::ifstream from(FileGetContent(path));

    if (from.is_open()) {
        while (getline(from, tmp)) {
            chunked.append(std::to_string(strlen(tmp.c_str())));
            chunked.append("\r\n");
            chunked.append(tmp + "\r\n");
            tmp.erase(0);
        }
    }
    from.close();
}

void            Headlines::searchKey(Request &requ, std::string &path) {
    req = requ;
    int pos;

    if (exists(path)) {
        intLenght = strlen(FileGetContent(path).c_str());
        if (intLenght > conf.limitClientBodySize) {
            transferEncoding = "chunked";
            processingChunk(path);
        }
        else {
            std::stringstream ss;
            ss << intLenght;
            contentLenght = ss.str();
        }
    }
    if (req.head.find("Accept") != req.head.end()) {
        if (req.query.method == "POST") {
            contentType = req.head["Content-Type"];
            if (std::string::npos != contentType.find(",")) {
                pos = contentType.find(",");
                contentType.erase(pos);
            }
        }
        else {
            contentType = req.head["Accept"];
            if (std::string::npos != contentType.find(",")) {
                pos = contentType.find(",");
                contentType.erase(pos);
            }
        }
    }
    if (!contentType.empty()) {
        if (contentType == "image/png" || contentType == "image/jpeg" || \
            contentType == "image/gif" || contentType == "text/html" || contentType == "application/javascript")
                expiresTime();
    }
    if (req.head.find("Accept-Ranges") != req.head.end())
        processingRange();
}

std::string     Headlines::getType() {
    return (this->contentType);
}

std::string     Headlines::getEncoding() {
    return (this->contentEncoding);
}

std::string     Headlines::getLenght() {
    return (this->contentLenght);
}

std::string     Headlines::getRange() {
    return (this->contentRange);
}

std::string     Headlines::getExpires() {
    return (this->expires);
}
