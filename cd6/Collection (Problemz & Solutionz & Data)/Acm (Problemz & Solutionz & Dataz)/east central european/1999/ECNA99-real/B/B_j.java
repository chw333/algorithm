/* Copyright John Bonomo (ACM ICPC ECNA 1999) */

import java.io.*;
import java.util.StringTokenizer;

public class B_j {

        public static final int MAX = 16;
        public static final int MAXNODES = 256+64+16+4+1;
        public static DataInputStream in = new DataInputStream(System.in);


        public static void processTree(node t[], node map[], int i, int size)
        {
                if (4*i+1 < size) {
                        processTree(t,map,4*i+1,size);
                        processTree(t,map,4*i+2,size);
                        processTree(t,map,4*i+3,size);
                        processTree(t,map,4*i+4,size);
                        int [] m = {0,1,2,3};
                        if (t[t[i].kids[m[0]]].minkid > t[t[i].kids[m[1]]].minkid) {
                                int tmp = m[0];
                                m[0] = m[1];
                                m[1] = tmp;
                        }
                        if (t[t[i].kids[m[1]]].minkid > t[t[i].kids[m[2]]].minkid) {
                                int tmp = m[1];
                                m[1] = m[2];
                                m[2] = tmp;
                        }
                        if (t[t[i].kids[m[2]]].minkid > t[t[i].kids[m[3]]].minkid) {
                                int tmp = m[2];
                                m[2] = m[3];
                                m[3] = tmp;
                        }
                        if (t[t[i].kids[m[0]]].minkid > t[t[i].kids[m[1]]].minkid) {
                                int tmp = m[0];
                                m[0] = m[1];
                                m[1] = tmp;
                        }
                        if (t[t[i].kids[m[1]]].minkid > t[t[i].kids[m[2]]].minkid) {
                                int tmp = m[1];
                                m[1] = m[2];
                                m[2] = tmp;
                        }
                        if (t[t[i].kids[m[0]]].minkid > t[t[i].kids[m[1]]].minkid) {
                                int tmp = m[0];
                                m[0] = m[1];
                                m[1] = tmp;
                        }
                        for(int j=0; j<4; j++)
                        map[i].kids[j] = m[j];
                        t[i].minkid = t[t[i].kids[m[0]]].minkid;
                }
                else {
                        map[i].kids[0] = -1;
                        map[i].kids[1] = -1;
                        map[i].kids[2] = -1;
                        map[i].kids[3] = -1;
                        t[i].minkid = t[i].val;
                }
        }

        public static void buildImage(node image[], node mapping[], int grid[][], int size,
                int i, int row, int col)
        {
                if (image[i].val != -1) {
                        for(int r=row; r<row+size; r++)
                        for(int c=col; c<col+size; c++)
                                        grid[r][c] = image[i].val;
                }
                else {
                        size /= 2;
                        buildImage(image, mapping, grid, size, 4*i+mapping[i].kids[0]+1, row, col);
                        buildImage(image, mapping, grid, size, 4*i+mapping[i].kids[1]+1, row, col+size);
                        buildImage(image, mapping, grid, size, 4*i+mapping[i].kids[2]+1, row+size, col);
                        buildImage(image, mapping, grid, size, 4*i+mapping[i].kids[3]+1, row+size, col+size);
                }
        }
        public static void main(String [] args)
        {
                int cases, size, nkids;
                node [] tree = new node[MAXNODES];
                node [] image = new node[MAXNODES];
                int [][] grid = new int [MAX][MAX];

                for(int i=0; i<MAXNODES; i++) {
                        tree[i] = new node();
                        image[i] = new node();
                }
                String line="";
                try {line = in.readLine();}     catch (IOException e) {}
                cases = Integer.parseInt(line);
                for(int c=1; c<=cases; c++) {
                        int s;
                        try {line = in.readLine();}     catch (IOException e) {}                        s = Integer.parseInt(line);
                        size = 0;
                        for(int i=1; i<=s; i *=2)
                        size += i*i;
                        for(int i=0; i<size;i++)
                        tree[i].val = image[i].val = -1;
                        try {line = in.readLine();}     catch (IOException e) {}                        nkids = Integer.parseInt(line);
                        for(int i=0; i<nkids; i++) {
                        int k, intensity;
                                try {line = in.readLine();}     catch (IOException e) {}
                                StringTokenizer str = new StringTokenizer(line);                                k = Integer.parseInt(str.nextToken());
                                intensity = Integer.parseInt(str.nextToken());
                                tree[k].val = intensity;
                        }
                        for(int k=0; k<size; k++) {
                        if (tree[k].val == -1) {
                                tree[k].kids[0] = 4*k+1;
                                        tree[k].kids[1] = 4*k+2;
                                tree[k].kids[2] = 4*k+3;
                                tree[k].kids[3] = 4*k+4;
                                }
                                else {
                                tree[k].kids[0] = -1;
                                tree[k].kids[1] = -1;
                                tree[k].kids[2] = -1;
                                tree[k].kids[3] = -1;
                                }
                        }
                        try {line = in.readLine();}     catch (IOException e) {}                        nkids = Integer.parseInt(line);
                        for(int i=0; i<nkids; i++) {
                        int k, intensity;
                                try {line = in.readLine();}     catch (IOException e) {}
                                StringTokenizer str = new StringTokenizer(line);                                k = Integer.parseInt(str.nextToken());
                                intensity = Integer.parseInt(str.nextToken());
                                image[k].val = intensity;
                        }
                        for(int k=0; k<size; k++) {
                        if (image[k].val == -1) {
                                image[k].kids[0] = 4*k+1;
                                        image[k].kids[1] = 4*k+2;
                                image[k].kids[2] = 4*k+3;
                                image[k].kids[3] = 4*k+4;
                                }
                                else {
                                image[k].kids[0] = -1;
                                image[k].kids[1] = -1;
                                image[k].kids[2] = -1;
                                image[k].kids[3] = -1;
                                }
                        }

                        node [] mapping = new node[MAXNODES];
                        for(int l=0; l<MAXNODES; l++)
                                mapping[l] = new node();
                        processTree(tree, mapping, 0, size);
                        buildImage(image, mapping, grid, s, 0, 0, 0);
                        System.out.println("Case " + c + "\n");
                        for(int r=0; r<s; r++) {
                                for(int col=0; col<s; col++) {
                                        String stmp = grid[r][col]+"";
                                        while (stmp.length() < 4)
                                                stmp = " "+stmp;
                                        System.out.print(stmp);
                                }
                                System.out.println();
                        }
                        if (c != cases)
                                System.out.println();
                }
        }
}

class node {
        public int val;
        public int [] kids;
        public int minkid;

        node()
        {
                kids = new int[4];
        }
};

