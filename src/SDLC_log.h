#define _2C (char*)
class SDLC_log
{
private:
 
public:
    SDLC_log(/* args */);
    void log(char *);
    void log(int );
    void msg(char *);
    void notice(char *);
    ~SDLC_log();
};
extern SDLC_log SDLC_LOG_;
