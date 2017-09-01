/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Anders Bolt-Evensen
 */
public class Edge {

    GrafNode u, v;
    double w;

    public Edge(GrafNode newU, GrafNode newV, double newW) {
        //System.out.println("GrafNode u: " + newU.toString() + "\nGrafNode v: " + newV.toString() + "\nvekt: " + newW);
        u = newU;
        v = newV;
        w = newW;
    }
}
