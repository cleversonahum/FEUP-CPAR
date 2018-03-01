class Aula1 {

	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("Invalid number of arguments");
			System.exit(0);
		}
		
		switch (Integer.parseInt(args[0])) {
                case 1:
                        multMatrix(Integer.parseInt(args[1]));
                        break;
                case 2:
                        mult2Matrix(Integer.parseInt(args[1]));
                        break;
        	}	
		
	}

	public static void multMatrix(int d) {
		
		int m1[] = new int[d*d];
		int m2[] = new int[d*d];
		int mult[] = new int[d*d];

		//Filling m1 and m2
		for(int i = 0; i<d*d;i++) {
			m1[i] = i+1;
			m2[i] = d*d-i;
		}

		//Filling mult
		for(int i=0; i<d*d;i++)
			mult[i] = 0;

		//Multiplying matrix 1 and 2
		for(int i=0; i<d; ++i)
			for(int j =0; j<d;++j)
				for(int k=0; k<d;++k) {
					mult[i*d+j] += m1[i*d+k] + m2[k*d+j];
				}
	}
	
	public static void mult2Matrix(int d) {
		
		int m1[] = new int[d*d];
		int m2[] = new int[d*d];
		int mult[] = new int[d*d];

		//Filling m1 and m2
		for(int i = 0; i<d*d;i++) {
			m1[i] = i+1;
			m2[i] = d*d-i;
		}

		//Filling mult
		for(int i=0; i<d*d;i++)
			mult[i] = 0;

		//Multiplying matrix 1 and 2
		for(int i=0; i<d; ++i)
			for(int k =0; k<d;++k)
				for(int j=0; j<d;++j) {
					mult[i*d+j] += m1[i*d+k] + m2[k*d+j];
				}
	}
}
