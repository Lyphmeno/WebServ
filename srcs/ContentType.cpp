#include "../incs/ContentType.hpp"

////////////////////////////////////////////////////////////////////////////////
//                              CONSTRUCTORS                                  //
////////////////////////////////////////////////////////////////////////////////

void ft::ContentType::initMime(std::string ext, std::string type)
{
    _mimeType[ext]._ext = ext;;
    _mimeType[ext]._type = type;
}

ft::ContentType::ContentType(void){

    initMime("aac", "audio/acc");
    initMime("abw", "application/x-abiword");
    initMime("arc", "application/octet-stream");
    initMime("avi", "video/x-msvideo");
    initMime("azw", "application/vnd.amazon.ebook");
    initMime("bin", "application/octet-stream");
    initMime("bmp", "image/bmp");
    initMime("bz", "application/x-bzip");
    initMime("bz2", "application/x-bzip2");
    initMime("csh", "application/x-csh");
    initMime("css", "text/css");
    initMime("csv", "text/csv");
    initMime("doc", "application/msword");
    initMime("docs", "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
    initMime("eot", "application/epub+zip");
    initMime("eot", "application/epub+zip");
    initMime("gif", "image/gif");
    initMime("htm", "text/html");
    initMime("html", "text/html");
    initMime("ico", "image/x-icon");
    initMime("ics", "text/calendar");
    initMime("jar", "application/java-archive");
    initMime("jpeg", "image/jpeg");
    initMime("jpg", "image/jpeg");
    initMime("js", "application/javascript");
    initMime("json", "application/json");
    initMime("mid", "audio/midi");
    initMime("midi", "audio/midi");
    initMime("mpeg", "video/mpeg");
    initMime("mpkg", "application/vnd.apple.installer+xml");
    initMime("odp", "application/vnd.oasis.opendocument.presentation");
    initMime("ods", "application/vnd.oasis.opendocument.spreadsheet");
    initMime("oga", "audio/ogg");
    initMime("odt", "application/vnd.oasis.opendocument.text");
    initMime("ogv", "video/ogg");
    initMime("ogx", "application/ogg");
    initMime("otf", "font/otf");
    initMime("png", "image/png");
    initMime("pdf", "application/pdf");
    initMime("ppt", "application/vnd.openxmlformats-officedocument.presentationml.presentation");
    initMime("rar", "application/x-rar-compressed");
    initMime("rtf", "application/rtf");
    initMime("sh", "application/x-sh");
    initMime("svg", "image/svg+xml");
    initMime("swf", "application/x-shockwave-flash");
    initMime("tar", "application/x-tar");
    initMime("tif", "image/tiff");
    initMime("tiff", "image/tiff");
    initMime("ts", "application/typescript");
    initMime("ttf", "font/ttf");
    initMime("vsd", "application/vnd.visio");
    initMime("wav", "audio/x-wav");
    initMime("weba", "audio/webm");
    initMime("webm", "video/webm");
    initMime("webp", "image/webm");
    initMime("woff", "font/woff");
    initMime("woff2", "font/woff2");
    initMime("xhtml", "application/xhtml+xml");
    initMime("xls", "application/vnd.ms-excel");
    initMime("xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
    initMime("xml", "application/xml");
    initMime("xul", "application/vnd.mozilla.xul+xml");
    initMime("zip", "application/zip");
    initMime("3gp", "video/3gpp");
    initMime("3gp", "audio/3gpp");
    initMime("3g2", "video/3gpp2");
    initMime("3g2", "audio/3gpp2");
    initMime("7z", "application/x-7z-compressed");
}

ft::ContentType::ContentType(const ContentType & src){
    *this = src;
}



////////////////////////////////////////////////////////////////////////////////
//                               DESTRUCTOR                                   //
////////////////////////////////////////////////////////////////////////////////

ft::ContentType::~ContentType(void){
}



////////////////////////////////////////////////////////////////////////////////
//                                OPERATORS                                   //
////////////////////////////////////////////////////////////////////////////////

ft::ContentType & ft::ContentType::operator=(ContentType const & value) {
    if (&value != this)
    {
    }
    return *this;
}

const std::string & ft::ContentType::getType(std::string extension){
    return _mimeType[extension]._type;
}