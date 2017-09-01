
import java.util.Iterator;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
public class EdgeList implements Iterable<Edge> {

    NodeListe head;

    /*
    * Linked list node class
    */
    static class NodeListe {
      
      NodeListe next, prev;
      Edge edge;

      public NodeListe(Edge edge) {

        this.edge = edge; 
        next = prev = null;
      
      }

    }

    /*
    * Insert a new edge into the neighbor list
    */
    void insert(Edge edge) {
      
      NodeListe x = new NodeListe(edge);
      x.next = head;
      
      if (head != null)
        head.prev = x;

      head = x;
      x.prev = null;

    }

    /*
    * Return an iterator for easy iteration through the edges in the neighbor 
    * list
    */
    public Iterator<Edge> iterator() {

      /*
      * Create an iterator by using an anonymous class that implements the 
      * Iterator interface
      */
      return new Iterator<Edge>() {

        NodeListe current;

        public boolean hasNext() { 
          
          if (current != null)
            return current.next != null;
          else
            return head != null;

        }

        public Edge next() {
          
          if (current == null)
            current = head;
          else 
            current = current.next;

          return current.edge;
        }
        
        public void remove() { return; }

      };

    }

    
}
