/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author aje
 */
public class PrioritetsKo {

    private GrafNode[] a;
    private int n;

    public PrioritetsKo(int storrelse) {
        a = new GrafNode[storrelse];
        n = 0;
    }

    public GrafNode minumum() {
        return a[0];
    }

    public void heapify(int i) {
        int venstre = 2 * i + 1;
        int hoyre = 2 * i + 2;
        int minst;
        if (venstre < n && a[venstre].hentAvstand() < a[i].hentAvstand()) {
            minst = venstre;
        } else {
            minst = i;
        }
        if (hoyre < n && a[hoyre].hentAvstand() < a[minst].hentAvstand()) {
            minst = hoyre;
        }
        if (minst != i) {
            GrafNode temp = a[minst];
            a[minst] = a[i];
            a[minst].settPos(minst);
            a[i] = temp;
            a[i].settPos(i);
            heapify(minst);
        }
    }

    public GrafNode extractMin() {
        n--;
        GrafNode min = a[0];
        a[0] = a[n];
        a[0].settPos(0);
        heapify(0);
        return min;
    }

    public void mink(GrafNode x, double d) {
        if (d > a[x.hentPos()].hentAvstand()) {
            return;
        }
        a[x.hentPos()].settAvstand(d);
        int forelder = (x.hentPos() - 1) / 2;
        while (x.hentPos() > 0 && a[forelder].hentAvstand() > a[x.hentPos()].hentAvstand()) {
            GrafNode temp = a[forelder];
            a[forelder] = a[x.hentPos()];
            a[x.hentPos()] = temp;
            a[x.hentPos()].settPos(x.hentPos());
            x.settPos(forelder);
            forelder = (x.hentPos() - 1) / 2;
        }
    }

    public void settInn(GrafNode node) {
        node.settPos(n);
        a[n] = node;
        mink(node, node.hentAvstand());
        n++;
    }

    public boolean erTom() {
        return n == 0;
    }
}
