/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
public interface MyIterator<T>{
    public boolean hasNext();
    public MyIterator<T> iterator();
    public int next();

    public void remove();
}
