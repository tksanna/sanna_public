import java.util.Comparator;

public class Attainment implements Comparable<Attainment> {
	private String courseCode;
	private String studentNumber; 
	private int grade;
	
	public static final Comparator<Attainment> CODE_STUDENT_CMP = new Comparator<>() {

		@Override
		public int compare(Attainment o1, Attainment o2) {
			int b = 0;
			int c = 0;
			b = o1.getCourseCode().compareTo(o2.getCourseCode());
			if (b == 0) {
				c = o1.getStudentNumber().compareTo(o2.getStudentNumber());
				return c;
			}
			return b;
		}};
		
		
	public static final Comparator<Attainment> CODE_GRADE_CMP = new Comparator<>() {
		
		@Override
		public int compare(Attainment o1, Attainment o2) {
			int b = 0;
			int c = 0;
			b = o1.getCourseCode().compareTo(o2.getCourseCode());
			if (b == 0) {
				c = o2.getGrade() - (o1.getGrade());
				return c;
			}
			return b;
		}};	
	
	//vertailee ensisijaisesti opiskelijanumeroita ja toissijaisesti kurssikoodeja.
	@Override
	public int compareTo(Attainment other) {
		int b = 0;
		int c = 0;
		b = getStudentNumber().compareTo(other.getStudentNumber());
		if (b == 0) {
			c = getCourseCode().compareTo(other.getCourseCode());
			return c;
		}
		return b;
	}

	public Attainment(String courseCode, String studentNumber, int grade) {
		super();
		this.courseCode = courseCode;
		this.studentNumber = studentNumber;
		this.grade = grade;
	}

	public String getCourseCode() {
		return courseCode;
	}

	public String getStudentNumber() {
		return studentNumber;
	}

	public int getGrade() {
		return grade;
	}
	
	//“kurssikoodi opiskelijanumero arvosana\n” 
	
	public String toString() {
		String str = String.format("%s %s %d\n" , courseCode, studentNumber, grade);
		return str;
	}
}
