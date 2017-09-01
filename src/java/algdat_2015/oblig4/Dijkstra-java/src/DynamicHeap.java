/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
public class DynamicHeap{
    private ArrayList<MyVertex> heap;
    private int heapSize;
 
    public DynamicHeap(ArrayList<MyVertex> heap, int heapSize) {
        this.heap = copy(heap);
        setHeapSize(heapSize);
    }

    public int getHeapSize() {
        return heapSize;
    }

    public void setHeapSize(int heapSize) {
        this.heapSize = heapSize;
    }

    public ArrayList<MyVertex> getHeap() {
        return heap;
    }

    public void buildHeap() {
        for (int i = getHeapSize() / 2; i >= 0; i--) {
            heapify(i);
        }
    }

    public void heapify(int index) {
        int left = left(index);
        int right = right(index);
        int min = index;

        if (left < getHeapSize() && heap.get(left).getDistance() <= heap.get(min).getDistance()) {
            min = left;
        }

        if (right < getHeapSize() && heap.get(right).getDistance() <= heap.get(min).getDistance()) {
            min = right;
        }

        if (min != index) {
            swap(min, index);
            heapify(min);
        }
    }

    public int parent(int index) {
        int tempIndex = index + 1;
        return (tempIndex / 2) - 1;
    }

    public int left(int index) {
        int tempIndex = index + 1;
        return (tempIndex * 2) - 1;
    }

    public int right(int index) {
        int tempIndex = index + 1;
        return (tempIndex * 2 + 1) - 1;
    }

    public void swap(int i, int j) {
        MyVertex temp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, temp);
    }

    private ArrayList<MyVertex> copy(ArrayList<MyVertex> heap) {
        ArrayList<MyVertex> copy = new ArrayList<>();
        //MyVertex vertex = new MyVertex(heap.size());
        for (MyVertex vertex : heap) {
            //while(heap.hasNext()){
            MyVertex vertexCopy = new MyVertex(vertex.getValue());
            vertexCopy.setDistance(vertex.getDistance());
            copy.add(vertexCopy);
        }

        for (MyVertex vertex : heap) {
            //while(heap.hasNext()){
            MyVertex vertexCopy = copy.get(copy.indexOf(vertex));
            MyVertex predecessor = copy.get(copy.indexOf(vertex.getPredecessor()));
            vertexCopy.setPredecessor(predecessor);

            for (Edge edge : vertex.getAdjacentVertices()) {
                MyVertex adjacentVertex = copy.get(copy.indexOf(edge.getTarget()));
                int weight = edge.getWeight();
                vertexCopy.addAdjacentVertex(new Edge(adjacentVertex, weight));
            }
        }
        return copy;
    }
}
