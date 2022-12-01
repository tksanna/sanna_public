/**
 * Implements a simple student register that maintains information about students, 
 * courses and course attainments.
 */

import java.util.ArrayList;
import java.util.Collections;

public class StudentRegister {

	public static final String COURSE_NAME_ORDER = "by name";
	public static final String COURSE_CODE_ORDER = "by code";

	private ArrayList<Student> studentlist = new ArrayList<Student>();
	private ArrayList<Attainment> attainmentlist = new ArrayList<Attainment>();
	private ArrayList<Course> courselist = new ArrayList<Course>();

	StudentRegister() {

	}

	public ArrayList<Student> getStudents() {
		Collections.sort(studentlist);
		return studentlist;
	}

	public ArrayList<Course> getCourses() {
		Collections.sort(courselist);
		return courselist;
	}

	public void addStudent(Student student) {
		studentlist.add(student);
	}

	public void addCourse(Course course) {
		courselist.add(course);
	}

	public void addAttainment(Attainment att) {
		attainmentlist.add(att);

	}

	private String getStudentName(String studentNum) {
		String studentName = "";
		for (Student stu : studentlist) {
			if (stu.getStudentNumber().equals(studentNum)) {
				studentName = stu.getName();
			}
		}
		return studentName;
	}

	private String getCourseName(String courseCode) {
		String courseName = "";
		for (Course cou : courselist) {
			if (cou.getCode().equals(courseCode)) {
				courseName = cou.getName();
			}
		}
		return courseName;
	}

	// tulostaa parametrina saatua opiskelijanumeroa vastaavan opiskelijan
	// kurssisuoritukset standarditulostevirtaan.
	public void printStudentAttainments(String studentNumber, String order) {
		ArrayList<Attainment> sorted = new ArrayList<>();
		for (Attainment s : attainmentlist) {
			if (s.getStudentNumber().equals(studentNumber)) {
				sorted.add(s);
			}

		}
		if (sorted.isEmpty()) {
			System.out.println("Unknown student number: " + studentNumber);
			return;
		} else {
			switch (order) {
			case (COURSE_NAME_ORDER):
				
				sorted.sort((a, b) -> {
					String coursecodeA;
					String coursenameA;
					String coursecodeB;
					String coursenameB;
					coursecodeA = a.getCourseCode();
					coursenameA = getCourseName(coursecodeA);
					coursecodeB = b.getCourseCode();
					coursenameB = getCourseName(coursecodeB);
					return coursenameA.compareTo(coursenameB);
				} );
				break;

			case (COURSE_CODE_ORDER):
				sorted.sort((a, b) -> a.getCourseCode().compareTo(b.getCourseCode()));
				break;
			default:
			}
		}

		String studentName = getStudentName(studentNumber);
		System.out.println(studentName + " (" + studentNumber + "):");

		for (Attainment s : sorted) {
			String courseName = getCourseName(s.getCourseCode());
			System.out.println("  " + s.getCourseCode() + " " + courseName + ": " + s.getGrade());
		}

	}

	public void printStudentAttainments(String studentNumber) {
		boolean isFound = false;
		String studentName = getStudentName(studentNumber);
		if (studentName.equals("") ) {
			System.out.println("Unknown student number: " + studentNumber);
			return;
		}
		System.out.println(studentName + " (" + studentNumber + "):");
		for (Attainment s : attainmentlist) {
			if (s.getStudentNumber().equals(studentNumber)) {
				String courseName = getCourseName(s.getCourseCode());
				System.out.println("  " + s.getCourseCode() + " " + courseName + ": " + s.getGrade());
				isFound = true;
			}
		}
		if (!isFound) {
			System.out.println("Unknown student number: " + studentNumber);
		}
	}

}
