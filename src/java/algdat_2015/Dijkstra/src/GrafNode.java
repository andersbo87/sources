/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Anders Bolt-Evensen
 */
public class GrafNode {

    private int id;
    private double avstand; // beregnet avstand
    private GrafNode forelder;
    private int pos; // posisjonen i prioritetskøen
    LinkList adj; // Dette er nabolisten.
    
    /**
     * Setter verdien til en node
     * @param nyID Den nye verdien
     */
    public void settID(int nyID) {
        id = nyID;
    }
    
    /**
     * Gir en node en forelder
     * @param nyForelder Den nye foreldernode
     */
    public void settForelder(GrafNode nyForelder) {
        forelder = nyForelder;
    }
    
    /**
     * Setter en posisjon i prioritetskøen
     * @param nyPos Den nye posisjonen i prioritetskøen
     */
    public void settPos(int nyPos) {
        pos = nyPos;
    }
    
    /**
     * Setter ny, beregnet avstand mellom nodene
     * @param nyAvstand Den nye avstanden som skal settes mellom nodene
     */
    public void settAvstand(double nyAvstand) {
        avstand = nyAvstand;
    }
    
    /**
     * Henter en avstand mellom 2 noder
     * @return avstanden mellom to noder
     */
    public double hentAvstand() {
        return avstand;
    }
    
    /**
     * Henter foreldrenoden til noden
     * @return Foreldrenoden til nåværende node
     */
    public GrafNode hentForelder() {
        return forelder;
    }
    /**
     * Henter posisjonen i prioritetskøen
     * @return Nodens posisjon i prioritetskøen
     */
    public int hentPos() {
        return pos;
    }
    
    /**
     * Henter ID-en til noden
     * @return ID-en til noden
     */
    public int hentID() {
        return id;
    }

    public GrafNode(int nyID) {
        id = nyID;
        adj = new LinkList();
        settAvstand(Double.POSITIVE_INFINITY);
        settForelder(null);
    }

    public void leggTilNabo(GrafNode v, double w) {
        adj.insert(new Edge(this, v, w));
    }
    
    /**
     * Henter stien mellom utgangspunktet og kantnodene.
     * @return en streng som inneholder stien mellom utgangspunktet og tilhørende kantnoder.
     */
    public String printPath()
    {
        if(hentForelder() == null)
            return Integer.toString(id);
        else
            return hentForelder().printPath() + " " + Integer.toString(id);
    }
    
    public String toString()
    {
        if(hentForelder() == null)
            return "NA";
        else
            return printPath() + " " + Double.toString(hentAvstand());
    }
}
