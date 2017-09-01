/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package week4;

/**
 *
 * @author andersbo
 */
public class NewClass {
    public static void doSomething(GenList list)
    {
        
    }
    public static void main(String[] args)
    {
        //ArrGenList<String> list = new ArrGenList<String>();
        ArrGenList<Integer> list = new ArrGenList<Integer>();
        LinkGenList<Integer> list2 = new LinkGenList<Integer>();
        doSomething(list);
        doSomething(list2);
    }
}
