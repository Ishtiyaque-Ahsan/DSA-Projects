/*
 MD ISHTIYAQUE AHSAN
 21COB300  , GL5503
 S. No.- 42 
 Implement Edmond Karp Algorith to find max flow in a graph network
 */
import javax.swing.*;
import java.awt.*;
import java.util.Arrays;
import java.util.Scanner;

public class edmond_karp{

    static class GraphVisualization extends JPanel {
        private  int[][] rrGraph;
    
        public GraphVisualization(int[][] rrGraph) {
            this.rrGraph= rrGraph;
        }
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int num_vertex = rrGraph.length;
            int vertex_radius = 30;
    
            // Vertices of graph numbered from 0 to num_vertex-1 are drawn here
            for (int i = 0; i < num_vertex; i++) { 
                int x = (int) (Math.cos(2 * Math.PI * i / num_vertex) * 150 + getWidth() / 2);
                int y = (int) (Math.sin(2 * Math.PI * i / num_vertex) * 150 + getHeight() / 2);
                // x and y are coordinates of vertex showing where vertex will positioned on outer circle
                g.setColor(Color.yellow);
                g.fillOval(x - vertex_radius, y - vertex_radius, 2 * vertex_radius, 2 * vertex_radius);
                g.setColor(Color.BLACK);
                g.drawString(String.valueOf(i), x, y); 
            }
    
            // Edges are drawn here from vertex i to vertext j
            for (int i = 0; i < num_vertex; i++) {
                for (int j = 0; j < num_vertex; j++) {
                    if (rrGraph[i][j] > 0) {
                        int x1 = (int) (Math.cos(2 * Math.PI * i / num_vertex) * 150 + getWidth() / 2);
                        int y1 = (int) (Math.sin(2 * Math.PI * i / num_vertex) * 150 + getHeight() / 2);
                        int x2 = (int) (Math.cos(2 * Math.PI * j / num_vertex) * 150 + getWidth() / 2);
                        int y2 = (int) (Math.sin(2 * Math.PI * j / num_vertex) * 150 + getHeight() / 2);
    
                        g.setColor(Color.RED);
                        g.drawLine(x1, y1, x2, y2);

                        // midpoint of edges
                        int midX = (x1 + x2) / 2;
                        int midY = (y1 + y2) / 2;
                        // write weight over edges
                        g.setColor(Color.BLACK);
                        g.drawString(String.valueOf(rrGraph[i][j]), midX, midY);
                    }
                }
            }       
        }
    }

    static class queue {
        private int size;
        private int front;
        private int back;
        private int[] arr;

        public queue(int n) {
            size = n;
            front = -1;
            back = -1;
            arr = new int[n];
        }

        public void push(int val) {
            back += 1;
            arr[back] = val;
        }

        public int pop() {
            front += 1;
            return arr[front];
        }

        public boolean empty() {
            if(front == back)
                return true;
            return false;
        }
    }
    
    static boolean bfs(int rGraph[][], int s, int t, int parent[], int V) {
        boolean[] visited = new boolean[V];
        queue q = new queue(V);
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.pop();
            for (int v = 0; v < V; v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    if (v == t) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return false;
    }

    static int karp(int graph[][], int s, int t, int V) {
        int[][] rGraph = new int[V][V];
        for (int u = 0; u < V; u++)
            for (int v = 0; v < V; v++)
                rGraph[u][v] = graph[u][v];
        
        JFrame frame = new JFrame("Graph Visualization of given input graph");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);

        GraphVisualization graphPanel = new GraphVisualization( graph);
        frame.add(graphPanel);
        graphPanel.revalidate();
        graphPanel.repaint();
        frame.setVisible(true);


        int[] parent = new int[V];  // to keep record of augmenting path as we move to sink
        int max_flow = 0;
        int C = 1;
       
        while (bfs(rGraph, s, t, parent, V)) {
            
            int min_cap = 999999;  //Integer.MAX_VALUE

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                min_cap = Math.min(min_cap, rGraph[u][v]);
            }

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                rGraph[u][v] -= min_cap;
                rGraph[v][u] += min_cap;
            }
           
            frame = new JFrame("Directed Graph Visualization " + C);        
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(400, 400);

            GraphVisualization graphPanel_1 = new GraphVisualization( rGraph);
            frame.add(graphPanel_1);
            graphPanel_1.revalidate();
            graphPanel_1.repaint();
            frame.setVisible(true);
        
            
            max_flow += min_cap;
            System.out.println("Augmenting Path : " + C);
            int y = t;
            while(y != s){
                int x = parent[y];
                System.out.print(y+" <- ");
                y=x;
            }
            System.out.println(s);
            System.out.println("Residual graph:");
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    System.out.print(rGraph[i][j] + " ");
                }
                System.out.println();
            }
            System.out.println("Flow added in Max_flow from this path : " + min_cap + "\n");
            C++;
        }
        return max_flow;
    }
     
    public static void main(String[] args) {
       
        int V = 6;
        int e = 10; //edges

        int[][] capacity = {
            {0, 2, 13,  0,  0,  0},
            {0, 0,  0,  6,  0,  0},
            {0, 9,  0,  8, 10,  7},
            {0, 0,  0,  0,  1,  5},
            {0 ,0,  0,  0,  0, 12},
            {0 ,0,  0,  0,  0,  0}
        };
       
        int s = 0;
        int t = 5;
        int maxFlow = karp(capacity, s, t,V );
        System.out.println("Maximum flow: " + maxFlow);    
    }   
/** *
    
    public static void main(String[] args) {
        int V = 0;
        System.out.print("Enter number of vertices : ");
        java.util.Scanner sc = new java.util.Scanner(System.in);
        V = sc.nextInt();
        int graph[][] = new int[V][V];

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                graph[i][j] = 0;
            }
        }

        int e = 0;
        int u = 0;
        int v = 0;
        int wt = 0;

        System.out.print("Enter no. of edges : ");
        e = sc.nextInt();
        System.out.println("Enter edges : ");
        System.out.println("u , v , wt : ");

        for (int i = 0; i < e; i++) {
            u = sc.nextInt();
            v = sc.nextInt();
            wt = sc.nextInt();
            graph[u][v] = wt;
        }

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                System.out.print(graph[i][j] + "      ");
            }
            System.out.println();
        }

        int s = 0;
        int t = 0;
        System.out.println("Enter source and destination : ");
        s = sc.nextInt();
        t = sc.nextInt();

        System.out.println("The maximum flow is " + karp(graph, s, t, V));

        sc.close();
    }**/
}

