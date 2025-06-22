---

### **Secure Software Development for Artemis Financial**

This repository showcases the application of secure software development principles and practices to enhance an existing web application for Artemis Financial, a financial consulting client.

---

#### **Client Overview: Artemis Financial**

Artemis Financial is a consulting company specializing in individualized financial plans for its customers, covering sensitive areas like savings, retirement, investments, and insurance. The company aimed to modernize its operations and, crucially, wanted to incorporate the latest and most effective software security measures to protect client data and financial information. My role involved enhancing their existing web application by adding secure communication mechanisms and ensuring compliance with modern software security requirements.

---

#### **Addressing Software Security Vulnerabilities**

In this project, a proactive approach was taken to identify and mitigate software security vulnerabilities. A combination of manual code review and automated static analysis proved highly effective. For instance, manual review allowed for the identification of critical issues like **hardcoded sensitive credentials** within configuration files (`application.properties`) and the use of **outdated dependencies** (`bcprov-jdk15on-1.46.jar` in `pom.xml`) known to contain numerous vulnerabilities.

Coding securely is paramount because it directly safeguards sensitive data, maintains user trust, ensures compliance with privacy regulations (e.g., GDPR, HIPAA), and protects the company from severe financial and reputational damage stemming from data breaches. Software security adds immense value to a company's overall well-being by building consumer confidence, reducing legal and financial risks, enhancing operational resilience, and demonstrating a commitment to data protection that aligns with industry best practices.

---

#### **Vulnerability Assessment: Challenges and Learnings**

The vulnerability assessment process presented both challenges and valuable learning opportunities. A significant challenge was troubleshooting persistent build failures with the OWASP Dependency-Check Maven plugin. Issues ranged from subtle XML parsing errors in the `suppression.xml` to critical `UpdateException` errors caused by the NVD (National Vulnerability Database) API requiring an API key, which had a lengthy activation period. This forced practical problem-solving to find workarounds, such as temporarily disabling NVD API communication to allow the build to complete for demonstration purposes. This experience reinforced the importance of meticulous configuration and adaptability when dealing with external tools and API changes.

Conversely, the systematic nature of static testing and the structured use of `keytool` for certificate generation were incredibly helpful. It provided a clear framework for identifying and addressing security concerns methodically.

---

#### **Increasing Layers of Security & Future Assessment**

To increase the layers of security in Artemis Financial's application, several key enhancements were implemented:

1.  **Secure Communications (HTTPS):** The application was refactored to use HTTPS, encrypting data in transit between the client and server. This involved configuring SSL settings in `application.properties` and deploying a self-signed certificate generated via Java Keytool.
2.  **Data Integrity (Checksum Verification):** A cryptographic checksum using SHA-256 was implemented for a unique data string, allowing for verification that data has not been tampered with.
3.  **Dependency Security Testing:** The OWASP Dependency-Check Maven plugin was integrated into the build process for static analysis of third-party libraries. This included configuring a `suppression.xml` file to manage and suppress identified vulnerabilities (such as `CVE-2023-20863` and others), ensuring a cleaner report for developers without unnecessary noise, especially for vulnerabilities that cannot be immediately patched in older frameworks.

In the future, to continually assess vulnerabilities and decide on mitigation techniques, I would advocate for integrating automated security testing even earlier in the Software Development Life Cycle (SDLC) – embracing a **DevSecOps** approach. This would include:
* Continuous Static Application Security Testing (SAST).
* Dynamic Application Security Testing (DAST).
* Interactive Application Security Testing (IAST).
* Threat Modeling.
* Security Playbooks and Automation.

---

#### **Ensuring Functionality and Security & Vulnerability Checks**

The application's functionality and security were ensured through rigorous testing. Functional testing involved accessing the refactored endpoints (e.g., `/hash` over HTTPS) in a web browser to confirm that data integrity checks were performed correctly and that secure communication was established (verified by `https://` and browser security indicators).

After refactoring the code, new vulnerabilities were checked for by running the OWASP Dependency-Check again. The tool was configured to produce a clean report (showing zero active vulnerabilities after suppression) to confirm that no new security flaws were inadvertently introduced through the changes. This process provided a clear demonstration that the refactored codebase compiled and executed without errors while maintaining a secure profile.

---

#### **Helpful Resources, Tools, and Coding Practices**

This assignment reinforced the value of several key resources, tools, and coding practices for future tasks:

* **Java Keytool:** Indispensable for generating and managing cryptographic keys and certificates.
* **OWASP Dependency-Check:** A powerful open-source tool for identifying vulnerabilities in third-party dependencies.
* **Maven:** Essential for project build automation and plugin management (like Dependency-Check).
* **Spring Boot:** Simplifies the development of production-ready, secure applications.
* **Secure Coding Practices:** Applying principles like avoiding hardcoded credentials, using strong algorithms (SHA-256, AES-256, RSA), and securing communication protocols (HTTPS).
* **DevSecOps Principles:** Integrating security tooling into the build pipeline to "shift left" security.
* **Troubleshooting Environment/Build Issues:** The experience of diagnosing and resolving complex Java/Maven environment variables (`JAVA_HOME`), NVD API connectivity, and intricate XML parsing errors will be invaluable.

---

#### **Showcasing Skills for Future Employers**

From this assignment, I would proudly show future employers the following to demonstrate my skills, knowledge, and experience:

* **Implemented Secure Communication (HTTPS):** Evidence of configuring and deploying HTTPS with self-signed certificates.
* **Implemented Data Integrity (Checksums):** Code and output demonstrating the use of cryptographic hashing for data verification.
* **Performed Static Application Security Testing:** "Before" and "After" Dependency-Check reports showcasing the ability to identify, analyze, and suppress vulnerabilities in third-party dependencies.
* **Troubleshooting Expertise:** The journey through various build errors (JDK paths, NVD API issues, XML parsing) highlights strong problem-solving and debugging skills in complex development environments.
* **Application of Secure Coding Best Practices:** The refactored code and the comprehensive report demonstrate a practical understanding of secure coding principles.
* **Understanding of Cybersecurity Concepts:** The written components reflect a solid grasp of topics like Certificate Authorities, access control, and the CIA triad.
* **Ability to Follow and Adapt Documentation:** Successfully navigating and implementing instructions from various technical guides (like Oracle Keytool docs and OWASP Dependency-Check guides).

---
