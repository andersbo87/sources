/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
public class Graph {
  private final linkList<MyVertex> vertexes;
  private final linkList<Edge> edges;

  public Graph(linkList<MyVertex> vertexes, linkList<Edge> edges) {
    this.vertexes = vertexes;
    this.edges = edges;
  }

  public linkList<MyVertex> getVertexes() {
    return vertexes;
  }

  public linkList<Edge> getEdges() {
    return edges;
  }
} 


