/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
public interface MyIterable<E> {
    public MyIterator<E> iterator(); 

    //public Iterable<Position<E>> positions();
}
