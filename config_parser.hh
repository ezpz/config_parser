#ifndef CONFIG_PARSER_HH__
#define CONFIG_PARSER_HH__

#include <string>
#include <fstream>
#include <map>
#include <cstdarg>

static std::string 
strip (const std::string &orig) {
    const std::string ws = " \t";
    std::string::size_type b = 0, e = 0;
    b = orig.find_first_not_of (ws);
    if (std::string::npos == b) { return orig; }
    e = orig.find_last_not_of (ws);
    if (std::string::npos == e) {
        return orig.substr (b);
    }
    return orig.substr (b, (e - b) + 1);
}

static std::string 
parse_section (const std::string &line) {
    std::string::size_type b = 0, e = 0;
    b = line.find ('[');
    if (std::string::npos == b) { return ""; }
    e = line.rfind (']'); 
    if (std::string::npos == e) { return ""; }
    return line.substr (b + 1, (e - b) - 1);
}

static std::pair< std::string, std::string > 
parse_kv (const std::string &line) {
    std::string sline = strip (line);
    std::string::size_type n = 0;
    n = sline.find ('=');
    if (std::string::npos == n) { return std::make_pair ("", ""); }
    std::string key = sline.substr (0, n);
    std::string value = sline.substr (n + 1);
    return std::make_pair (strip(key), strip(value));
}

class ConfigFile {

    typedef typename std::map< std::string, std::string > KeyValType;
    typedef typename std::map< std::string, KeyValType > SectionType;

    bool verbose_;

    std::string section_; /* current section during parse */

    SectionType sections_;

    void Msg (const char *fmt, ...) const {
        if (! verbose_) { return; }
        va_list va;
        va_start (va, fmt);
        vfprintf (stdout, fmt, va);
        va_end (va);
    }

    void ParseLine (const std::string &line) {
        std::string sline = strip(line);
        if (sline.empty ()) { return; }
        if ('#' == sline[0] || ';' == sline[0]) { return; }
        if ('[' == sline[0]) { 
            std::string sec = parse_section (sline);
            if (! sec.empty ()) {
                Msg ("New section: [%s] => [%s]\n", 
                        section_.c_str (), sec.c_str ());
                section_ = sec; 
            } else {
                Msg ("Failed to assign new section\n");
            }
            return;
        }
        std::pair< std::string, std::string > kv = parse_kv (sline);
        if (kv.first.empty ()) { 
            Msg ("Failed to assign K=V\n");
            return; 
        }
        Msg ("%s::%s <- '%s'\n", section_.c_str (), 
                kv.first.c_str (), kv.second.c_str ());
        sections_[section_][kv.first] = kv.second;
    }

    void ParseFile (const char *fname) {
        section_ = "";
        std::ifstream cfg(fname);
        std::string line;
        while (getline (cfg, line)) {
            Msg ("INPUT: '%s'\n", line.c_str ());
            ParseLine (line);
        }
    }

public:

    ConfigFile (const std::string &fname, bool verbose = false) :
        verbose_(verbose) { 
        ParseFile (fname.c_str ()); 
    }

    ConfigFile (const char *fname, bool verbose = false) : verbose_(verbose) { 
        ParseFile (fname); 
    }

    std::string Get (const std::string &section, const std::string &key);
    std::string Get (const std::string &key) { return Get("",key); }
};

std::string ConfigFile::Get (const std::string &sec, const std::string &key) {
    SectionType::iterator s = sections_.find (sec);
    if (sections_.end () == s) {
        return "";
    }
    KeyValType::iterator kv = s->second.find (key);
    if (s->second.end () == kv) {
        return "";
    }
    return kv->second;
}

#endif /*CONFIG_PARSER_HH__*/