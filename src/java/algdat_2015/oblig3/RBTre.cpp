#include <iostream>
#include <sstream>
#include <fstream>
#include <signal.h>
#include <math.h>
#include <limits.h>
#include <queue>
#include <deque>
#include <stack>
#include <unistd.h>
#include <sys/time.h>
#include <stdexcept>
#include <cstdlib>
using namespace std;
const char *prog_name;
bool innsetting, fillesing, sletting;
int tot, ins;
//template <class T>
class RBNode{
private:
    bool roed;
    int verdi;
    RBNode/*<T>*/ *venstre, *hoyre, *forelder;
public:
    RBNode(int verdi)
    {
        this->roed = true;
        this->verdi = verdi;
        /*
         De neste 3 linjene initialiserer de tre nodene venstre, 
         * høyre (skrevet hoyre i koden) og forelder til 0x0. 
         * "0x0" kan også skrives "NULL" og tilsvarer skrivemåten "null" i Java.
         */
        venstre = 0x0;
        hoyre = 0x0;
        forelder = 0x0;
    }
    void nyFarge()
    {
        if(this->roed)
            this->roed = false;
        else
            this->roed = true;
    }
    bool erRoed()
    {
        if(!this->roed)
            return false;
        return roed;
    }
    int hentVerdi()
    {
        //return this->verdi;
        if(!verdi)
        {
            throw std::runtime_error("verdi er null.\n");
        }
        return verdi;
    }
    RBNode *hentVenstre()
    {
        return this->venstre;
    }
    RBNode *hentHoyre()
    {
        return this->hoyre;
    }
    RBNode *hentForelder()
    {
        return this->forelder;
    }
    void clearParent()
    {
        this->forelder = 0x0;
    }
    void settVenstre(RBNode *venstre)
    {
        this->venstre = venstre;
        if(venstre)
            venstre->forelder = this;
    }
    void settHoyre(RBNode *hoyre)
    {
        this->hoyre = hoyre;
        if(hoyre)
            hoyre->forelder = this;
    }
}; // slutt på klassen RBNode.

//template <class T>
class RBTre {
  public:
    RBNode *rot;
  private:
    // Indre implementasjon av de 3 basiske funksjonalitetene…
    RBNode *aksesserNode(RBNode *node, int verdi)
    {
        if(!node)
        {
            return 0x0;
        }
        if(node->hentVerdi() == verdi)
        {
            return node;
        }
        else if(node->hentVerdi() > verdi)
        {
            if(!node->hentVenstre())
                return 0x0;
            else
            {
                return this->aksesserNode(node->hentVenstre(), verdi);
            }
        }
        else
        {
            if(!node->hentHoyre())
            {
                return 0x0;
            }
            else
            {
                return this->aksesserNode(node->hentHoyre(), verdi);
            }
        }
    }
    void settInnNodeDriver(RBNode *node, int verdi)
    {
        if(!node)
            return;
        RBNode *innsettingsNode = 0x0;
        if(node->hentVerdi() == verdi)
        {
            return;
        }
        else if(node->hentVerdi() > verdi)
        {
            if(!node->hentVenstre())
            {
                innsettingsNode = new RBNode(verdi);
                node->settVenstre(innsettingsNode);
            }
            else
            {
                settInnNodeDriver(node->hentVenstre(), verdi);
            }
        }
        else
        {
            if(!node->hentHoyre())
            {
                innsettingsNode = new RBNode(verdi);
                node->settHoyre(innsettingsNode);
            }
            else
            {
                settInnNodeDriver(node->hentHoyre(), verdi);
            }
        }
        if(!innsettingsNode)
            return;
        /*this->*/fiksDobbelRoedProblem(node);
        innsettingsNode = 0x0;
    }
    
    void slettNodeDriver(RBNode *node, int verdi)
    {
        if(!node)
            return;
        if(node->hentVerdi() == verdi)
        {
            RBNode *lengstVenstreFraHoyre;
            if(!node->hentVenstre())
                lengstVenstreFraHoyre = node->hentHoyre();
            else if(!node->hentHoyre())
                lengstVenstreFraHoyre = node->hentVenstre();
            else if(!node->hentVenstre()->hentHoyre())
                lengstVenstreFraHoyre = node->hentVenstre();
            else if(!node->hentHoyre()->hentVenstre())
                lengstVenstreFraHoyre = node->hentHoyre();
            else
            {
                lengstVenstreFraHoyre = node->hentHoyre()->hentVenstre();
                while(lengstVenstreFraHoyre->hentVenstre())
                {
                    lengstVenstreFraHoyre = lengstVenstreFraHoyre->hentVenstre();
                }
            }
            if(!lengstVenstreFraHoyre)
            {
                if(node->hentVenstre())
                {
                    node->hentVenstre()->nyFarge();
                }
                else if(node->hentHoyre())
                    node->hentHoyre()->nyFarge();
                else if(!node->erRoed())
                    gjenopprettRedusertHoeyde(node);
            }
            else
            {
                if(lengstVenstreFraHoyre->hentVenstre())
                    lengstVenstreFraHoyre->hentVenstre()->nyFarge();
                else if(lengstVenstreFraHoyre->hentHoyre())
                    lengstVenstreFraHoyre->hentHoyre()->nyFarge();
                else if(!lengstVenstreFraHoyre->erRoed())
                    gjenopprettRedusertHoeyde(lengstVenstreFraHoyre);
                if(lengstVenstreFraHoyre != node->hentVenstre() && lengstVenstreFraHoyre != node->hentHoyre())
                    lengstVenstreFraHoyre->hentForelder()->settVenstre(lengstVenstreFraHoyre->hentHoyre());
                
                if(lengstVenstreFraHoyre != node->hentVenstre() && node->hentVenstre())
                    lengstVenstreFraHoyre->settVenstre(node->hentVenstre());
                if(lengstVenstreFraHoyre != node->hentHoyre() && node->hentHoyre())
                    lengstVenstreFraHoyre->settHoyre(lengstVenstreFraHoyre->hentHoyre());
                if(node->erRoed() && !lengstVenstreFraHoyre->erRoed())
                    lengstVenstreFraHoyre->nyFarge();
                if(!node->erRoed() && lengstVenstreFraHoyre->erRoed())
                    lengstVenstreFraHoyre->nyFarge();
            }
            if(node->hentForelder())
            {
                if(node->hentForelder()->hentVenstre() == node)
                    node->hentForelder()->settVenstre(lengstVenstreFraHoyre);
                else
                    node->hentForelder()->settHoyre(lengstVenstreFraHoyre);
            }
            else
            {
                node = lengstVenstreFraHoyre;
                if(node)
                    node->clearParent();
            }
            delete node;
        }
        else if(node->hentVerdi() > verdi)
        {
             if(!node->hentVenstre())
             {}
             else
                 slettNodeDriver(node->hentVenstre(), verdi);
        }
        else
        {
            if(!node->hentHoyre())
            {}
            else
                slettNodeDriver(node->hentHoyre(), verdi);
        }
    }
    
    void fiksDobbelRoedProblem(RBNode *node)
    {
        if(!node->erRoed())
        {
            return;
        }
        // roter mot høyre
        if(node == node->hentForelder()->hentVenstre())
        {
            if(!node->hentForelder()->hentHoyre() || !node->hentForelder()->hentHoyre()->erRoed())
                hoeyreRoter(node);
            else
            {
                node->nyFarge();
                node->hentForelder()->hentHoyre()->nyFarge();
                node->hentForelder()->nyFarge();
                if(!node->hentForelder()->hentForelder())
                {
                    node->hentForelder()->nyFarge();
                    return;
                }
                fiksDobbelRoedProblem(node->hentForelder()->hentForelder());
            }
        }
        // roter mot venstre
        else
        {
            if(!node->hentForelder()->hentVenstre() || !node->hentForelder()->hentVenstre()->erRoed())
                venstreRoter(node);
            else
            {
                node->nyFarge();
                node->hentForelder()->hentVenstre()->nyFarge();
                node->hentForelder()->nyFarge();
                if(!node->hentForelder()->hentForelder())
                {
                    node->hentForelder()->nyFarge();
                    return;
                }
                fiksDobbelRoedProblem(node->hentForelder()->hentForelder());
            }
        }
    }
    void venstreRoter(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        if(node->hentVenstre() && node->hentVenstre()->erRoed())
        {
            RBNode *barn = node->hentVenstre();
            node->settVenstre(barn->hentHoyre());
            barn->settHoyre(node);
            forelder->settHoyre(barn);
            node = barn;
        }
        node->nyFarge();
        forelder->nyFarge();
        // Foerlders høyrenode -> Rots venstrenode.
        forelder->settHoyre(node->hentVenstre());
        
        if(forelder->hentForelder())
        {
            // Bind roten til resten av treet.
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
            node = rot;
        }
        node->settVenstre(forelder);
    }
    void hoeyreRoter(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        if(node->hentHoyre() && node->hentHoyre()->erRoed())
        {
            RBNode *barn = node->hentHoyre();
            node->settHoyre(barn->hentVenstre());
            barn->settVenstre(node);
            forelder->settVenstre(barn);
            node = barn;
        }
        node->nyFarge();
        forelder->nyFarge();
        // Foerlders høyrenode -> Rots venstrenode.
        forelder->settVenstre(node->hentHoyre());
        
        if(forelder->hentForelder())
        {
            // Bind noden til resten av treet.
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
            node = rot;
        }
        // Nodens høyrebarn
        node->settHoyre(forelder);
    }
    
    // Funksjonaliteter for balansering: redusert høyde og fjerning
    void gjenopprettRedusertHoeyde(RBNode *node)
    {
        if(!node)
            return;
        RBNode *forelder = node->hentForelder();
        if(!forelder)
            return;
        if(node == forelder->hentVenstre())
        {
            if(forelder->erRoed())
            {
                if((forelder->hentHoyre()->hentVenstre() && forelder->hentHoyre()->hentVenstre()->erRoed()) || (forelder->hentHoyre()->hentHoyre() && forelder->hentHoyre()->hentHoyre()->erRoed()))
                {
                    // tilfelle 1.1 venstre
                    foersteVRotering(forelder->hentHoyre());
                }
                else
                {
                    // tilfelle 1.2 venstre
                    forelder->hentForelder()->nyFarge();
                    forelder->nyFarge();
                }
            }
            else
            {
                if(forelder->hentForelder()->erRoed())
                {
                    if((forelder->hentHoyre()->hentVenstre()->hentHoyre() && forelder->hentHoyre()->hentVenstre()->hentHoyre()->erRoed()) || (forelder->hentHoyre()->hentVenstre()->hentVenstre() && forelder->hentHoyre()->hentVenstre()->hentVenstre()->erRoed()))
                    {
                        // tilfelle 2.1.1 venstre
                        andreVRotering(forelder->hentHoyre());
                    }
                    else
                    {
                        // tilfelle 2.1.2 venstre
                        tredjeVRotering(forelder->hentHoyre());
                    }
                }
                else
                {
                    if((forelder->hentHoyre()->hentVenstre() && forelder->hentHoyre()->hentVenstre()->erRoed()) || (forelder->hentHoyre()->hentHoyre() && forelder->hentHoyre()->hentHoyre()->erRoed()))
                    {
                        // tilfelle 2.2.1 venstre
                        fjerdeVRotering(forelder->hentHoyre());
                    }
                    else
                    {
                        // tilfelle 2.2.2 venstre
                        forelder->hentHoyre()->nyFarge();
                        if(forelder->hentForelder())
                            gjenopprettRedusertHoeyde(forelder);
                    }
                }
            }
        }
        else
        {
            if(forelder->erRoed())
            {
                if((forelder->hentVenstre()->hentVenstre() && forelder->hentVenstre()->hentVenstre()->erRoed()) || (forelder->hentVenstre()->hentHoyre() && forelder->hentVenstre()->hentHoyre()->erRoed()))
                {
                    // tilfelle 1.1 høyre
                    foersteHRotering(forelder->hentVenstre());
                }
                else
                {
                    // tilfelle 1.2 høyre
                    forelder->hentVenstre()->nyFarge();
                    forelder->nyFarge();
                }
            }
            else
            {
                if(forelder->hentVenstre()->erRoed())
                {
                    if(!forelder->hentVenstre()->hentHoyre()) 
                        return; // har egentlig ikke peiling på hva som bør gjøres, så tar bare og bryter ut av funksjonen
                    if((forelder->hentVenstre()->hentHoyre()->hentHoyre() && forelder->hentVenstre()->hentHoyre()->hentHoyre()->erRoed()) || (forelder->hentVenstre()->hentHoyre()->hentVenstre() && forelder->hentVenstre()->hentHoyre()->hentVenstre()->erRoed()))
                    {
                        // tilfelle 2.1.1 høyre
                        andreHRotering(forelder->hentVenstre());
                    }
                    else
                    {
                        // tilfelle 2.1.2 høyre
                        tredjeHRotering(forelder->hentVenstre());
                    }
                }
                else
                {
                    if((forelder->hentVenstre()->hentVenstre() && forelder->hentVenstre()->hentVenstre()->erRoed()) || (forelder->hentVenstre()->hentHoyre() && forelder->hentVenstre()->hentHoyre()->erRoed()))
                    {
                        // tilfelle 2.2.1 høyre
                        fjerdeHRotering(forelder->hentVenstre());
                    }
                    else
                    {
                        // tilfelle 2.2.2 høyre
                        forelder->hentVenstre()->nyFarge();
                        if(forelder->hentForelder())
                            gjenopprettRedusertHoeyde(forelder);
                    }
                }
            }
        }
    }
    // VRotering = venstrerotering.
    void foersteVRotering(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        if(node->hentVenstre() && node->hentVenstre()->erRoed())
        {
            RBNode *barn = node->hentVenstre();
            node->settVenstre(barn->hentHoyre());
            barn->settHoyre(node);
            node = barn;
            forelder->nyFarge();
        }
        else
        {
            node->hentHoyre()->nyFarge();
            node->nyFarge();
            forelder->nyFarge();
        }
        forelder->settHoyre(node->hentVenstre());
        if(forelder->hentForelder())
        {
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
            node = rot;
        }
        node->settVenstre(forelder);
    }
    void andreVRotering(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        RBNode *besteForelder = forelder->hentForelder();
        if(node->hentVenstre()->hentVenstre() && node->hentVenstre()->hentVenstre()->erRoed())
        {
            RBNode *barn = node->hentVenstre()->hentVenstre();
            node->hentVenstre()->settVenstre(barn->hentHoyre());
            barn->settHoyre(node->hentVenstre());
            node->settVenstre(barn);
            barn->hentHoyre()->nyFarge();
            barn->nyFarge();
        }
        forelder->settHoyre(node->hentVenstre()->hentVenstre());
        node->hentVenstre()->settVenstre(forelder);
        node->settVenstre(node->hentVenstre()->hentHoyre());
        node->hentVenstre()->nyFarge();
        forelder->hentForelder()->settHoyre(node);
        if(besteForelder)
        {
            if(besteForelder->hentVenstre() == forelder)
                besteForelder->settVenstre(forelder->hentForelder());
            else
                besteForelder->settHoyre(forelder->hentForelder());
        }
        else
        {
            rot = forelder->hentForelder();
            rot->clearParent();
        }
    }
    void tredjeVRotering(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        node->hentVenstre()->nyFarge();
        forelder->settHoyre(node->hentVenstre());
        node->nyFarge();
        if(forelder->hentForelder())
        {
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
        }
        node->settVenstre(forelder);
    }
    void fjerdeVRotering(RBNode *node)
    {
        RBNode *forelder = rot->hentForelder();
        if(node->hentVenstre() && node->hentVenstre()->erRoed())
        {
            RBNode *barn = node->hentVenstre();
            node->settVenstre(barn->hentHoyre());
            barn->settHoyre(node);
            forelder->settHoyre(barn);
            node = barn;
            node->nyFarge();
        }
        else
        {
            rot->hentHoyre()->nyFarge();
        }
        forelder->settHoyre(node->hentVenstre());
        if(forelder->hentForelder())
        {
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
            node = rot;
        }
        rot->settVenstre(forelder);
    }
    
    // HRotering = Høyrerotering.
    void foersteHRotering(RBNode *node)
    {
        if(!node)
        {}
        RBNode *forelder=node->hentForelder();
        if(node->hentHoyre() && node->hentHoyre()->erRoed())
        {
            RBNode *barn = node->hentHoyre();
            node->settHoyre(barn->hentVenstre());
            barn->settVenstre(node);
            forelder->settVenstre(barn);
            node = barn;
            forelder->nyFarge();
        }
        else
        {
            node->hentVenstre()->nyFarge();
            node->nyFarge();
            forelder->nyFarge();
        }
        forelder->settVenstre(node->hentHoyre());
        if(forelder->hentForelder())
        {
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
            node = rot;
        }
        rot->settHoyre(forelder);
    }
    void andreHRotering(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        RBNode *besteForelder = forelder->hentForelder();
        if(node->hentHoyre()->hentHoyre() && node->hentHoyre()->hentHoyre()->erRoed())
        {
            RBNode *barn = node->hentHoyre()->hentHoyre();
            node->hentHoyre()->settHoyre(barn->hentVenstre());
            barn->settVenstre(node->hentHoyre());
            node->settHoyre(barn);
            barn->hentVenstre()->nyFarge();
            barn->nyFarge();
        }
        forelder->settVenstre(node->hentHoyre()->hentHoyre());
        node->hentHoyre()->settHoyre(forelder);
        node->settHoyre(node->hentHoyre()->hentHoyre());
        node->hentHoyre()->nyFarge();
        forelder->hentForelder()->settVenstre(node);
        if(besteForelder)
        {
            if(besteForelder->hentVenstre() == forelder)
                besteForelder->settVenstre(forelder->hentForelder());
            else
                besteForelder->settHoyre(forelder->hentForelder());
        }
        else
        {
            rot = forelder->hentForelder();
            rot->clearParent();
        }

    }
    void tredjeHRotering(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        node->hentHoyre()->nyFarge();
        forelder->settVenstre(node->hentHoyre());
        node->nyFarge();
        if(forelder->hentForelder())
        {
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
        }
        node->settHoyre(forelder);
    }
    void fjerdeHRotering(RBNode *node)
    {
        RBNode *forelder = node->hentForelder();
        if(node->hentHoyre() && node->hentHoyre()->erRoed())
        {
            RBNode *barn = node->hentHoyre();
            node->settHoyre(barn->hentVenstre());
            barn->settVenstre(node);
            forelder->settVenstre(barn);
            node = barn;
            node->nyFarge();
        }
        else
        {
            node->hentVenstre()->nyFarge();
        }
        forelder->settVenstre(node->hentHoyre());
        if(forelder->hentForelder())
        {
            if(forelder->hentForelder()->hentVenstre() == forelder)
                forelder->hentForelder()->settVenstre(node);
            else
                forelder->hentForelder()->settHoyre(node);
        }
        else
        {
            rot = node;
            rot->clearParent();
            node = rot;
        }
        node->settHoyre(forelder);
    }
public:
    RBTre()
    {
        this->rot = 0x0;
    }
    bool erTom()
    {
        return rot == 0x0;
    }
    
    // de tre basiskte funksjonen (funksjoner som kan kalles fra andre klasser)
    RBNode *aksesserNode(int verdi)
    {
        if(this->erTom())
        {
            return 0x0;
        }
        else
            return this->aksesserNode(rot, verdi);
    }
    void settInnNode(int verdi)
    {
        if(!rot)
        {
            rot = new RBNode(verdi);
            rot->nyFarge();
        }
        else
            settInnNodeDriver(rot, verdi);
    }
    void slettNode(int verdi)
    {
        if(!rot)
        {
            cerr << "Noden " << verdi << " er tom." << endl;
            return;
        }
        else
            slettNodeDriver(rot, verdi);
    }
    
    void inorderTraversering()
    {
        this->inorderTraverseringDriver(this->rot);
        fprintf(stdout, "\n");
    }
    
    void inorderTraverseringDriver(RBNode *node)
    {
        if(node->erRoed())
	    fprintf(stdout, "\033[31m(\033[0m");
        else
            fprintf(stdout, "(");
        if(node->hentVenstre())
        {
            inorderTraverseringDriver(node->hentVenstre());
            fprintf(stdout, " ");
        }
        if(node->erRoed()) // Hvis noden er rød, skal verdien skrives ut med rød skrift, dersom terminalen støtter dette (hvis ikke blir utskriften ganske kryptisk…
                fprintf(stdout, "\033[31m%d\033[0m", node->hentVerdi());
        else
                fprintf(stdout, "%d", node->hentVerdi());
        if(node->hentHoyre())
        {
            fprintf(stdout, " ");
            inorderTraverseringDriver(node->hentHoyre());
        }
	if(node->erRoed())
	    fprintf(stdout, "\033[31m)\033[0m");
	else
	    fprintf(stdout, ")");
    }
};

class RBTreIO
{
private:
    string *minStreng;
public:
    RBTreIO()
    {
        minStreng = 0x0; //initialiserer minStreng...
    }
    ~RBTreIO()
    {
        
    }
    string *readArray(const char *filename)
    {
        /*Les fra fil*/
        ifstream in(filename);
        if(!in)
        {
            fprintf(stderr, "%s: Kan ikke lese filen %s.\n", prog_name, filename);
            exit(1); // avslutter programmet istedenfor å returnere en tom tabell.
        }
        string str2 = " ";
        stringstream buffer;
        buffer << in.rdbuf();
        string test = buffer.str();
        int last = test.size() -1;
        if(last >= 0 && test[last] != ' ') // dersom innholdet i filen ikke ender med mellomrom
        {
            /*
             * Legger til et mellomrom på slutten av strengen.
             * Dette fordi funksjonen genererer en nullpointer dersom strengen ikke ender
             * med et mellomrom. 
             */
            string spc = " ";
            test.append(spc);
        }
        size_t pos1 = 0;
        size_t pos2;
        size_t str_pos1 = 0;// str_pos2;
        int count = 0;
        while((str_pos1 = test.find(str2, str_pos1)) < test.length())
        {
            str_pos1 += str2.length();
            count++;
        }
        static string *str; str = new string[count];
        //fprintf(stdout, "Lengden på tabellen: %d\n", count);
        if(count == 0)
        {
            fprintf(stderr, "%s: Lengden på tabellen er for liten. Lengden på tabellen må være >= 0.\n", prog_name);
            exit(1); // avlsutter programmet istedenfor å returnere en tom tabell.
        }
        for(int x = 0; x < count; x++){
            pos2 = test.find(" ", pos1);
            str[x] = test.substr(pos1, (pos2-pos1));
            //if(x != 0){
            //    long l = strtol(str[x].c_str(), NULL, 10);
            //}
            pos1 = pos2+1;
        }
        minStreng = str;
        return minStreng;
    }
};

void catch_sigsegv(int signum)
{
    signal(SIGSEGV, catch_sigsegv);
    fprintf(stderr, "Det ser ut til at det er en feil i programmet som gjør at programmet må avsluttes. Hvis du har aktivert støtte for \"core dumps\", vil det bli opprettet nå.\n");
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}

void catch_siginfo(int signum)
{
  #ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
    fprintf(stdout, "Programmet jobber med oppretting, søking i og sletting av noder i et rødsvart tre. :)\n");
    if(fillesing == true)
      fprintf(stdout, "Leser filen. Dette kan ta litt tid.\n");
    if(innsetting == true)
      fprintf(stdout, "Setter inn node %d av %d.\n", ins, tot);
  #endif
}

//#define array_size(array) (sizeof((array))/sizeof((array[0])))
int main(int argc, const char **argv)
{
    signal(SIGSEGV, catch_sigsegv);
#ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
#endif
    prog_name = "RBTre";
    if(argc < 2 || argc > 3)
    {
        fprintf(stderr, "bruk: \t%s fil1\n\t%s fil1 fil2\n", prog_name, prog_name);
        return 1;
    }
    try
    {
        struct timeval totStart, totEnd, insStart, insEnd, searchStart, searchEnd, delStart, delEnd;
        long mtime_ins, mtime_search, mtime_del, totTime;
        gettimeofday(&totStart, NULL);

        RBTre *tree = new RBTre();
        RBTreIO *io = new RBTreIO();
        string *str;
	fillesing = true;
        str = io->readArray(argv[1]);
        int instot = atoi(str[0].c_str());
	tot = instot;
        int i;
	fillesing = false;
	innsetting = true;
        gettimeofday(&insStart, NULL);
        for(i = 1; i <= instot; i++)
        {
	  ins = i;
            tree->settInnNode(atoi(str[i].c_str()));
        }
        gettimeofday(&insEnd, NULL);
	innsetting = false;
	fprintf(stdout, "Rotnode: %d\n", tree->rot->hentVerdi());
        fprintf(stdout, "Traverserer inOrder:\n");
        tree->inorderTraversering();
        gettimeofday(&searchStart, NULL);
        if(tree->aksesserNode(6))
        {
            fprintf(stdout, "Node med verdi 6 ble funnet.\n");
        }
        else
        {
            fprintf(stderr, "Node med verdi 6 ble ikke funnet.\n");
        }
        gettimeofday(&searchEnd, NULL);
        if(tree->aksesserNode(1000000))
        {
            fprintf(stdout, "Node med verdi 1000000 ble funnet.\n");
        }
        else
        {
            fprintf(stderr, "Node med verdi 1000000 ble ikke funnet.\n");
        }
        if(argc == 3)
        {
            string *del_str;
            del_str = io->readArray(argv[2]);
            int deltot = 0, i = 0;
            deltot = atoi(del_str[0].c_str());
            gettimeofday(&delStart, NULL);
            for(i=1; i<= deltot; i++)
            {
                tree->slettNode(atoi(del_str[i].c_str()));
            }
            gettimeofday(&delEnd, NULL);
            mtime_ins = searchEnd.tv_sec - searchStart.tv_sec;
            mtime_search = searchEnd.tv_sec - searchStart.tv_sec;
            mtime_del = delEnd.tv_sec - delStart.tv_sec;
            fprintf(stdout, "Traversering inOrder etter sletting av noder…\n");
            tree->inorderTraversering();
            gettimeofday(&totEnd, NULL);
            totTime = totEnd.tv_sec - totStart.tv_sec;
	    if(totTime == 0){
                long totTime_usec = totEnd.tv_usec - totStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på hele runddansen.\n", totTime_usec);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på hele runddansen.\n", totTime);
            if(mtime_ins == 0){
                long mtime_ins_usec = mtime_ins = searchEnd.tv_usec - searchStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å sette inn %d noder.\n", mtime_ins_usec, instot);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å sette inn %d noder.\n", mtime_ins, instot);
            if(mtime_search == 0){
                long mtime_search_usec = searchEnd.tv_usec - searchStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å søke etter node 6.\n", mtime_search_usec);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å søke etter node 6.\n", mtime_search);
            if(mtime_del == 0){
                long mtime_del_usec = delEnd.tv_usec - delStart.tv_usec;
                fprintf(stdout, "Programmet brukte %ld mikrosekunder på å slette %d noder.\n",mtime_del_usec, deltot);
            }
            else
                fprintf(stdout, "Programmet brukte %ld sekunder på å slette %d noder.\n", mtime_del, deltot);
            return 0;
        }
        mtime_ins = insEnd.tv_sec - insStart.tv_sec;
        mtime_search = searchEnd.tv_sec - searchStart.tv_sec;
        gettimeofday(&totEnd, NULL);
        totTime = totEnd.tv_sec - totStart.tv_sec;
        if(totTime == 0){
            long totTime_usec = totEnd.tv_usec - totStart.tv_usec;
            fprintf(stdout, "Programmet brukte %ld mikrosekunder på hele runddansen.\n", totTime_usec);
        }
        else
            fprintf(stdout, "Programmet brukte %ld sekunder på hele runddansen.\n", totTime);
        if(mtime_ins == 0){
            long mtime_ins_usec = mtime_ins = searchEnd.tv_usec - searchStart.tv_usec;
            fprintf(stdout, "Programmet brukte %ld mikrosekunder på å sette inn %d noder.\n", mtime_ins_usec, instot);
        }
        else
            fprintf(stdout, "Programmet brukte %ld sekunder på å sette inn %d noder.\n", mtime_ins, instot);
        if(mtime_search == 0){
            long mtime_search_usec = searchEnd.tv_usec - searchStart.tv_usec;
            fprintf(stdout, "Programmet brukte %ld mikrosekunder på å søke etter node 5.\n", mtime_search_usec);
        }
        else
            fprintf(stdout, "Programmet brukte %ld sekunder på å søke etter node 5.\n", mtime_search);
        return 0;
    }
    catch(exception &e)
    {
        fprintf(stderr, "%s: Her er det noe som ikke er som det skal: %s\n", prog_name, e.what());
        return 2;
    }
}
