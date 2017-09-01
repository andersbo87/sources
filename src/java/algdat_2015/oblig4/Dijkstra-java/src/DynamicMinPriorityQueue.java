/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
public class DynamicMinPriorityQueue {
     private DynamicHeap dynamicHeap;

  public DynamicMinPriorityQueue() {
    dynamicHeap = new DynamicHeap(new ArrayList<MyVertex>(), 0);
  }

  public int size() {
    return dynamicHeap.getHeapSize();
  }

  public MyVertex getMin() {
    checkHeapSize();
    return dynamicHeap.getHeap().get(0);
  }

  public void prioritizeQueue() {
    dynamicHeap.buildHeap();
  }

  public MyVertex extractMin() {
    checkHeapSize();
    ArrayList<MyVertex> heap = dynamicHeap.getHeap();
    MyVertex vertex = heap.get(0);

    int heapSize = dynamicHeap.getHeapSize();
    heap.set(0, heap.get(heapSize - 1));
    dynamicHeap.setHeapSize(--heapSize);
    dynamicHeap.heapify(0);

    return vertex;
  }

  public void decreaseKey(int index, int key) {
    checkHeapSize();
    ArrayList<MyVertex> heap = dynamicHeap.getHeap();

    if (heap.get(index).getDistance() < key) {
      throw new IllegalArgumentException("New key is bigger than current key: " + key + " > "
          + heap.get(index).getDistance());
    }

    MyVertex vertex = heap.get(index);
    vertex.setDistance(key);

    while (index > 0
        && heap.get(dynamicHeap.parent(index)).getDistance() > heap.get(index).getDistance()) {
      dynamicHeap.swap(dynamicHeap.parent(index), index);
      index = dynamicHeap.parent(index);
    }
  }

  public void insert(MyVertex vertex) {
    int newHeapSize = dynamicHeap.getHeapSize() + 1;
    dynamicHeap.setHeapSize(newHeapSize);
    ArrayList<MyVertex> heap = dynamicHeap.getHeap();
    heap.add(vertex);
    decreaseKey(newHeapSize - 1, vertex.getDistance());
  }

  private void checkHeapSize() {
    if (dynamicHeap.getHeapSize() < 1) {
      throw new IllegalStateException("Heap is empty.");
    }
  }

  @Override
  public String toString() {
    return dynamicHeap.getHeap().toString();
  }
}

