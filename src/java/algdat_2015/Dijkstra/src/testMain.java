
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.Random;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author andersbo
 */
public class testMain {
    
    public GrafNode[] liste;
    public PrioritetsKo q;

    PrioritetsKo opprettKo() {
        PrioritetsKo ret = new PrioritetsKo(liste.length);
        for (GrafNode v : liste) {
            ret.settInn(v);
        }
        return ret;
    }

    public void init(GrafNode s) {
        s.settAvstand(0);
    }

    public void relax(Edge edge) {
        if (edge.v == null) {
            return;
        }
        if (edge.v.hentAvstand() <= edge.u.hentAvstand() + edge.w) {
            return;
        }
        q.mink(edge.v, edge.u.hentAvstand() + edge.w);
        edge.v.settForelder(edge.u);
    }

    public void dijkstra(GrafNode s) {
        init(s);
        q = opprettKo();
        while (!q.erTom()) {
            GrafNode u = q.extractMin();
            for (Edge e : u.adj) {
                relax(e);
            }
        }
    }
    private static final double MB = 1024L * 1024L;
    /**
     * Konverterer bytes til megabytes når det gjelder måling av minnebruk
     * @param bytes Verdien som skal konverteres til MB
     */
    static double convertToMegabytes(long bytes)
    {
        return bytes/MB;
    }
    public static void main(String args[]) {
        try 
        {
            if(args.length != 1)
            {
                System.err.println("Usage: Dijkstra arg1 where arg1 is the number of nodes and what's worse to be created.");
                return;
            }
            Runtime rt = Runtime.getRuntime();
	    rt.gc();
	    rt.gc();
            Dijkstra l = new Dijkstra();
            int i = 0, j = 0;
            int maks = 0;
            float testNr = 0.0f;
            maks = Integer.parseInt(args[0]);
            l.liste = new GrafNode[maks];
            long innsettingsStart = System.currentTimeMillis();
            for(j = 0; j < maks; j++){
                l.liste[j] = new GrafNode(j);
            }
            Random r = new Random(Long.parseLong(args[0]));
            for(i = 0; i < Integer.parseInt(args[0]); i++){
                for(j = 0; j< Integer.parseInt(args[0]); j++)
                {
                    testNr = r.nextFloat();
                    if(testNr > 0.8f && i != j){
                        l.liste[i].leggTilNabo(l.liste[j], testNr*5);
                    }
                }
            }
            long insMem = rt.totalMemory() - rt.freeMemory();
            long innsettingStopp = System.currentTimeMillis();
            long innsettingsTot = innsettingStopp - innsettingsStart;
            //long sokStart = System.currentTimeMillis();
	    long allSearches = 0;
	    Random r2 = new Random();
            int n;
	    for(i= 0; i< 10; i++){
		n = r2.nextInt(maks);
                System.out.println("n:" + n);
		long sokStart = System.currentTimeMillis();
		l.dijkstra(l.liste[n]);
		for (GrafNode v : l.liste) {
		    System.out.println(v.toString());
		}
		long sokStopp = System.currentTimeMillis();
		long thisSearch = sokStopp-sokStart;
		allSearches = allSearches + thisSearch;
                for(GrafNode v : l.liste){
                    v.settForelder(null);
                    v.settAvstand(Double.POSITIVE_INFINITY);
                }
                System.out.println("Dette søket tok " + thisSearch + " millisekunder.");
	    }
            long searchMem = rt.totalMemory()-rt.freeMemory();
	    double avgSearch = allSearches / 10;
            //long sokStopp = System.currentTimeMillis();
            //long sokTot = sokStopp - sokStart;
            System.out.println("Systemet brukte " + innsettingsTot + " millisekunder på å sette inn nodene.");
            System.out.println("Systemet brukte gjennomsnittlig " + avgSearch + " millisekunder på å søke seg gjennom nodene.");
            System.out.println("Minnebruk\n"
                    + "Under innsetting: " + convertToMegabytes(insMem) + " MB\n"
                    + "Under søking    : " + convertToMegabytes(searchMem-insMem) + " MB");
        }   
        /*catch (FileNotFoundException fnfe) {
            System.out.println(fnfe.getMessage());
        }*/ 
        catch (Exception e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
    }
}
