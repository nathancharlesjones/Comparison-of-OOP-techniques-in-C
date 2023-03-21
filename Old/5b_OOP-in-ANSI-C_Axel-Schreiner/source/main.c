#include "mallard.h"

int
main (int argc __attribute__((unused)), char ** argv)
{	
    void * p;

    initMallard();
    
    while (* ++ argv)
    {	
        switch (** argv)
        {
            case 'm':
                p = new(Mallard, "Freida", BROWN);
                migrate(p);
                break;
            case 'd':
                p = new(Duck, "Freida");
                break;
            default:
                continue;
        }
        show(p);
        quack(p);
        delete(p);
    }
    return 0;
}
