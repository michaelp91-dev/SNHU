# CS-320 Software Test Automation & QA Portfolio

## Professional Self-Assessment
Throughout this course, I have developed a rigorous mindset regarding software quality. Moving beyond simple coding, I now view software development as a discipline that requires verification at every step. My work with JUnit and Maven has shown me that automated testing is not just a safety net, but a design tool that leads to cleaner, more maintainable code.

## Journal Reflections

### 1. How can I ensure that my code, program, or software is functional and secure?
Ensuring functionality and security starts with comprehensive **Unit Testing**. In this course, I learned to use JUnit to achieve high code coverage, ensuring that every logic branch—including edge cases like null values or boundary limits—was verified. 

For security, I learned that defensive coding is key. By writing tests that specifically try to break the application (e.g., passing invalid IDs or overly long strings), I can prevent data corruption and potential vulnerabilities before the code ever reaches production. Functional tests prove the software does what it is supposed to do, while security-minded tests prove it doesn't do what it isn't supposed to do.

### 2. How do I interpret user needs and incorporate them into a program?
Interpreting user needs requires translating vague requirements into concrete, testable conditions. For Project One, the "user needs" were strict constraints on data (e.g., "Contact ID cannot be longer than 10 characters"). 

I incorporated these by adopting a test-first mentality. Before writing the logic, I looked at the requirements and asked, "How would I test this?" This forced me to verify user constraints immediately within the code logic (using `if` statements and exceptions), ensuring that the final software aligned perfectly with what the client asked for.

### 3. How do I approach designing software?
My approach to software design has shifted toward **modularity and testability**. I now design classes (like the `Contact` object) to be distinct from their management logic (the `ContactService`). This separation of concerns allows me to test individual components in isolation without dependencies breaking the entire suite. 

When designing, I also consider "maintainability." By writing clear, self-documenting code and accompanying it with a robust test suite, I ensure that future developers (or myself) can refactor or add features to the software without fear of causing regression bugs.

## Portfolio Artifacts
Included in this repository are the artifacts from Project One:
* `Contact.java`
* `ContactService.java`
* `ContactTest.java`
* `ContactServiceTest.java`

These files demonstrate my ability to write standard Java code and, more importantly, my ability to write the corresponding automated tests to verify that code.

