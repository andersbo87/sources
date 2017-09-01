/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Anders Bolt-Evensen
 */
import java.io.*;

public class Dijkstra {

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
            if(args.length != 2)
            {
                System.err.println("Usage: Dijkstra file1 arg1, where arg 1 is sthe starting point of the algorithm.");
                return;
            }
            Runtime rt = Runtime.getRuntime();
            Dijkstra l = new Dijkstra();
            FileReader fr = new FileReader(args[0]);
            BufferedReader br = new BufferedReader(fr);
            String linje;
            int i = 0;
            int maks = 0;
            String[] splittetLinje = null;
            linje = br.readLine();
            maks = Integer.parseInt(linje);
            l.liste = new GrafNode[maks];
            long innsettingsStart = System.nanoTime();
            for (int j = 0; j < maks; j++) {
                l.liste[j] = new GrafNode(j);
            }
            while ((linje = br.readLine()) != null) {
                splittetLinje = linje.split(" ");
                l.liste[Integer.parseInt(splittetLinje[0])].leggTilNabo(l.liste[Integer.parseInt(splittetLinje[1])], Double.parseDouble(splittetLinje[2]));
                l.liste[Integer.parseInt(splittetLinje[1])].leggTilNabo(l.liste[Integer.parseInt(splittetLinje[0])], Double.parseDouble(splittetLinje[2]));
                i++;
            }
            long insMem = rt.totalMemory() - rt.freeMemory();
            long innsettingStopp = System.nanoTime();
            long innsettingsTot = innsettingStopp - innsettingsStart;
            br.close();
            fr.close();
            rt.gc(); // kjører garbage collector for å frigjøre minne, slik at vi også kan måle hvor mye minne som brukes under søking.
            long sokStart = System.nanoTime();
            l.dijkstra(l.liste[Integer.parseInt(args[1])]);
            for (GrafNode v : l.liste) {
                System.out.println(v.toString());
            }
            long sokStopp = System.nanoTime();
            long sokTot = sokStopp - sokStart;
            double sek = innsettingsTot / 1000000000;
            System.out.println("Systemet brukte " + sek + " sekunder på å sette inn nodene.");
            System.out.println("Systemet brukte " + sokTot + " nanosekunder på å søke seg gjennom nodene.");
            System.out.println("Minnebruk\n"
                    + "Under innsetting: " + convertToMegabytes(insMem) + " MB\n");
        } 
        catch (FileNotFoundException fnfe) {
            System.out.println(fnfe.getMessage());
        } 
        catch (Exception e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
    }
}
