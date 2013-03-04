// Copyright (C) 1999 Lucent Technologies
// From 'Programming Pearls' by Jon Bentley

// SortAnim.java -- Animate sorting algorithms

import java.applet.*;
import java.awt.*;
import java.util.Date;

public class SortAnim extends Applet {
	// Screen Elements
	private TextField n_text;
	private Choice dist_choices;
	private Choice alg_choices;
	private Button run_button;
	private Label msg_label;
	private Color draw_color = Color.black;
	private Color back_color = Color.white;

// SORTING DATA AND ALGS

	static private final int MAXN = 10000;
	static private int n=100;
	static private float a[] = new float[MAXN];

	// Sorting: Generate Inputs
	static private final int GEN_RAND = 0;
	static private final int GEN_ASCEND = 1;
	static private final int GEN_DESCEND = 2;
	static private int gen_num = GEN_RAND;

	private void genarray()
	{	for (int i = 0; i < n; i++) {
			switch(gen_num) {
			case GEN_RAND: a[i] = (float) Math.random(); break;
			case GEN_ASCEND: a[i] = ((float) i)/n; break;
			case GEN_DESCEND: a[i] = (float) (1.0 - ((float) i)/n); break;
			}
		}
	}

	// Sorting: Supporting Algs
	private void baseswap(int i, int j)
	{	float t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	// Sorting: Animation Support
	static private final int MINX = 20, MAXX = 580;
	static private final int MINY = 50, MAXY = 380;
	static private float factorx, factory;
	static private boolean wantanim = true;

	private void initdisplay()
	{	Graphics g = this.getGraphics();
		Rectangle r = this.bounds();
		g.setColor(back_color);
		g.fillRect(r.x, r.y, r.width, r.height);
		factorx = ((float) MAXX-MINX) / n;
		factory = ((float) MAXY-MINY);
	}

	private void draw(int i, Color c)
	{	Graphics g = this.getGraphics();  // BETTER WAY?
		int d = 4;
		int px = (int) (MINX + factorx*i);
		int py = MAXY - (int)(factory*a[i]);
		g.setColor(c);
		g.drawOval(px, py, d, d);
	}

	private void swap(int i, int j)
	{	if (wantanim) {
			draw(i, back_color);
			draw(j, back_color);
		}
		baseswap(i, j);
		if (wantanim) {
			draw(i, draw_color);
			draw(j, draw_color);
		}
	}

	// Sorting Algs
	private void isort()
	{	for (int i = 1; i < n; i++)
			for (int j = i; j > 0 && a[j-1] > a[j]; j--)
				swap(j-1, j);
	}	

	private void ssort()
	{	for (int i = 0; i < n-1; i++)
			for (int j = i; j < n; j++)
				if (a[j] < a[i])
					swap(i, j);
	}

	private void shellsort()
	{	int i, j, h;
		for (h = 1; h < n; h = 3*h + 1)
			;
		for (;;) {
			h /= 3;
			if (h < 1) break;
			for (i = h; i < n; i++) {
				for (j = i; j >= h; j -= h) {
					if (a[j-h] < a[j]) break;
					swap(j-h, j);
				}
			}
		}
	}

	private void siftdown(int l, int u)
	{	int i, c;
		i = l;
		for (;;) {
			c = 2*i;
			if (c > u)
				break;
			if (c+1 <= u && a[c+1] > a[c])
				c++;
			if (a[i] >= a[c])
				break;
			swap(i, c);
			i = c;
		}
	}

	private void heapsort() // BEWARE!!! Sorts x[1..n-1]
	{	int i;
		for (i = n/2; i > 0; i--)
			siftdown(i, n-1);
		for (i = n-1; i >= 2; i--) {
			swap(1, i);
			siftdown(1, i-1);
		}
	}

	private void qsort(int l, int u)
	{	if (l >= u)
			return;
		int m = l;
		for (int i = l+1; i <= u; i++)
			if (a[i] < a[l])
				swap(++m, i);
		swap(l, m);
		qsort(l, m-1);
		qsort(m+1, u);
	}

	void qsort2(int l, int u)
	{	if (l >= u)
			return;
		int i = l;
		int j = u+1;
		for (;;) {
			do i++; while (i <= u && a[i] < a[l]);
			do j--; while (a[j] > a[l]);
			if (i > j)
				break;
			swap(i, j);
		}
		swap(l, j);
		qsort2(l, j-1);
		qsort2(j+1, u);
	}

	// Drive Sort
	static private final int ALG_ISORT = 0;
	static private final int ALG_SELSORT = 1;
	static private final int ALG_SHELLSORT = 2;
	static private final int ALG_HSORT = 3;
	static private final int ALG_QSORT = 4;
	static private final int ALG_QSORT2 = 5;
	static private int alg_num = ALG_ISORT;

	private void dosort()
	{	switch(alg_num) {
		case ALG_ISORT:     isort(); break;
		case ALG_SELSORT:   ssort(); break;
		case ALG_SHELLSORT: shellsort(); break;
		case ALG_HSORT:     heapsort(); break;
		case ALG_QSORT:     qsort(0, n-1); break;
		case ALG_QSORT2:    qsort2(0, n-1); break;
		}
	}

	private void runanim()
	{	n = Integer.parseInt(n_text.getText());
		if (n < 1 || n > MAXN) {
			n = 50;
			n_text.setText("" + n);
		}
		initdisplay();
		msg_label.setText("Running");
		genarray();
		for (int i = 0; i < n; i++)
			draw(i, draw_color);
		Date timer = new Date();
		long start = timer.getTime();
		dosort();
		timer = new Date();
		long msecs = timer.getTime() - start;
		msg_label.setText("Msecs: " + msecs);
		if (! wantanim) // Draw results over input
			for (int i = 0; i < n; i++)
				draw(i, draw_color);
	}

// GUI FUNCTIONS
	public void init() {
		this.setBackground(back_color);

		// TextField for n (problem size)
		n_text = new TextField(5);
		this.add(new Label("n:"));
		this.add(n_text);
		n_text.setText("" + n);

		// Choice of Starting distributions
		dist_choices = new Choice();
		dist_choices.addItem("Random");
		dist_choices.addItem("Ascending");
		dist_choices.addItem("Descending");
		this.add(new Label("Input:"));
		this.add(dist_choices);

		// Choice of Sort Algorithms
		alg_choices = new Choice();
		alg_choices.addItem("Insertion Sort");
		alg_choices.addItem("Selection Sort");
		alg_choices.addItem("Shell Sort");
		alg_choices.addItem("Heap Sort");
		alg_choices.addItem("Quicksort");
		alg_choices.addItem("2-way Quicksort");
		this.add(new Label("Algorithm:"));
		this.add(alg_choices);

		// Run Button
		run_button = new Button("Run");
		this.add(run_button);

		// Message Label
		msg_label = new Label("                   ");
		this.add(msg_label);
	}

	public boolean action(Event event, Object arg) {
		if (event.target == dist_choices) {
			if (arg.equals("Random")) gen_num = GEN_RAND;
			else if (arg.equals("Ascending")) gen_num = GEN_ASCEND;
			else if (arg.equals("Descending")) gen_num = GEN_DESCEND;
			return true;
		} else if (event.target == alg_choices) {
			if (arg.equals("Insertion Sort")) alg_num = ALG_ISORT;
			else if (arg.equals("Selection Sort")) alg_num = ALG_SELSORT;
			else if (arg.equals("Shell Sort")) alg_num = ALG_SHELLSORT;
			else if (arg.equals("Heap Sort")) alg_num = ALG_HSORT;
			else if (arg.equals("Quicksort")) alg_num = ALG_QSORT;
			else if (arg.equals("2-way Quicksort")) alg_num = ALG_QSORT2;
			return true;
		} else if (event.target == run_button) {
			runanim();
			return true;
		} else
			return super.action(event, arg);
	}
}