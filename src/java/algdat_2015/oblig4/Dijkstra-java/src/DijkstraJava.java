/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.*;
/**
 *
 * @author andersbo
 */

public class DijkstraJava 
{
    private int distance;
    public DynamicMinPriorityQueue queue;
    public int getShortestPath(ArrayList<MyVertex> graph, MyVertex source) {
        init(graph, source);
        while (queue.size() > 0) 
        {
            MyVertex vertex = queue.extractMin();
            distance = vertex.getDistance();
            for (Edge edge : vertex.getAdjacentVertices()) {
                relax(vertex, edge);
            }
            queue.prioritizeQueue();
        }
        return distance;
    }

    public int getShortestPath(ArrayList<MyVertex> graph, MyVertex source, MyVertex target) 
    {
        init(graph, source);

        while (queue.size() > 0) {
            MyVertex vertex = queue.extractMin();
            distance = vertex.getDistance();

            if (vertex.equals(target)) {
                break;
            }

            for (Edge edge : vertex.getAdjacentVertices()) {
                relax(vertex, edge);
            }
            queue.prioritizeQueue();
        }
    return distance;
    }

    private void init(ArrayList<MyVertex> graph, MyVertex source) {
        distance = 0;
        initSingleSource(graph, source);
        queue = new DynamicMinPriorityQueue();
        for (MyVertex vertex : graph) {
            queue.insert(vertex);
        }
    }

    private void initSingleSource(ArrayList<MyVertex> graph, MyVertex source) 
    {
        //,MyVertex vertex = new MyVertex(graph.size());
        for (MyVertex vertex : graph) {
        //while(graph.hasNext()){
            if (vertex.equals(source)) {
                vertex.setDistance(0);
            } 
            else 
            {
                vertex.setDistance(Integer.MAX_VALUE);
            }
            vertex.setPredecessor(null);
        }
    }

    private void relax(MyVertex source, Edge edge) 
    {
        MyVertex target = edge.getTarget();
        int newDistance = source.getDistance() + edge.getWeight();

        if (target.getDistance() > newDistance) {
            target.setDistance(newDistance);
            target.setPredecessor(source);
        }
    }
    public static void main(String args[])
    {
        String prog_name = "DijkstraJava";
        try{
            DijkstraJava dj = new DijkstraJava();
            if(args.length != 1)
            {
                System.err.println("usage: " + prog_name + " file1");
                System.exit(1);
            }
            FileReader fr = new FileReader(args[0]);
            BufferedReader br = new BufferedReader(fr);
            String linje;
            int i = 0;
            int maks = 0;
            String[] splittetLinje = null;
            linje = br.readLine();
            maks = Integer.parseInt(linje);
            
            //dj.init(ArrayList<MyVertex> graph, MyVertex source);
            MyVertex mv = new MyVertex(maks);
            mv.addAdjacentVertex(null);
            dj.init(null, null);
            dj.getShortestPath(null, null);
            long innsettingsStart = System.nanoTime();
            Edge edge;
            while((linje = br.readLine()) != null)
            {
                splittetLinje = linje.split(" ");
                edge = new Edge(new MyVertex(Integer.parseInt(splittetLinje[2])), Integer.parseInt(splittetLinje[2]));
                mv.addAdjacentVertex(edge);
                i++;
            }
            linkList<MyVertex> llmv = new linkList<>();
            linkList<Edge> lledge = new linkList<>();
            llmv.insert(0);
            Graph g = new Graph(llmv, lledge);
            dj.getShortestPath(null, mv);
        }
        /*catch(FileNotFoundException fe)
        {
            System.err.println(prog_name + " En feil har oppstått: " + fe.getMessage());
        }*/
        catch(Exception e)
        {
            System.err.println(prog_name + ": En feil har oppstått: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
