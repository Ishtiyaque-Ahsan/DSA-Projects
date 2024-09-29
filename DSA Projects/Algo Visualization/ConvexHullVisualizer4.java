// working

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class ConvexHullVisualizer4 extends JFrame {
    private ArrayList<Point> points;

    public ConvexHullVisualizer4() {
        super("Convex Hull");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 500);
        setVisible(true);
        points = new ArrayList<>();
        addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                points.add(new Point(e.getX(), e.getY()));
                repaint();
            }
        });
    }

    public void paint(Graphics g) {
        super.paint(g);
        for (Point p : points) {
            g.fillOval(p.x - 2, p.y - 2, 4, 4);
        }

        if (points.size() > 2) {
            ArrayList<Point> hull = convexHull(points);
            g.setColor(Color.RED); // Set the line color to red
            Point prev = hull.get(0);
            for (int i = 1; i < hull.size(); i++) {
                Point current = hull.get(i);
                g.drawLine(prev.x, prev.y, current.x, current.y);
                prev = current;
            }
            g.drawLine(prev.x, prev.y, hull.get(0).x, hull.get(0).y);
        }
    }

    private Point findLowestPoint(ArrayList<Point> points) {
        if (points.isEmpty())
            return null;

        Point lowest = points.get(0);
        for (Point p : points) {
            if (p.y < lowest.y || (p.y == lowest.y && p.x < lowest.x)) {
                lowest = p;
            }
        }
        return lowest;
    }

    private ArrayList<Point> convexHull(ArrayList<Point> points) {
        if (points.size() < 3)
            return new ArrayList<>(points);

        Point lowest = findLowestPoint(points);
        points.sort(Comparator.comparingDouble(p -> Math.atan2(p.y - lowest.y, p.x - lowest.x)));

        ArrayList<Point> stack = new ArrayList<>();
        stack.add(points.get(0));
        stack.add(points.get(1));

        for (int i = 2; i < points.size(); i++) {
            Point top = stack.remove(stack.size() - 1);
            while (ccw(stack.get(stack.size() - 1), top, points.get(i)) <= 0) {
                top = stack.remove(stack.size() - 1);
            }
            stack.add(top);
            stack.add(points.get(i));
        }

        return stack;
    }

    private int ccw(Point a, Point b, Point c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    public static void main(String[] args) {
        new ConvexHullVisualizer4();
    }
}

