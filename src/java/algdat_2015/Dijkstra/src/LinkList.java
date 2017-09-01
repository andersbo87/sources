/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.Iterator;

/**
 *
 * @author Anders Bolt-Evensen
 */
public class LinkList implements Iterable<Edge> {

    NaboNode hode;

    class NaboNode {

        private NaboNode neste, forrige;
        Edge edge;

        public void settNeste(NaboNode nyNeste) {
            neste = nyNeste;
        }

        public void settForrige(NaboNode nyForrige) {
            forrige = nyForrige;
        }

        public NaboNode hentForrige() {
            return forrige;
        }

        public NaboNode hentNeste() {
            return neste;
        }

        public NaboNode(Edge newEdge) {
            edge = newEdge;
        }
    }

    public void insert(Edge edge) {
        NaboNode x = new NaboNode(edge);
        x.settNeste(hode);
        if (hode != null) {
            hode.settForrige(x);
        }
        hode = x;
        x.settForrige(null);
    }

    public Iterator<Edge> iterator() {
        return new Iterator<Edge>() {
            NaboNode gjeldende;

            public boolean hasNext() {
                if (gjeldende != null) {
                    return gjeldende.hentNeste() != null;
                } else {
                    return hode != null;
                }
            }

            public Edge next() {
                if (gjeldende == null) {
                    gjeldende = hode;
                } else {
                    gjeldende = gjeldende.hentNeste();
                }
                return gjeldende.edge;
            }

            public void remove() {
                return;
            }
        };
    }
}
