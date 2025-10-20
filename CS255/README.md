### **CS 255 Systems Analysis and Design: Portfolio Reflection**

#### **Briefly summarize the DriverPass project. Who was the client? What type of system did they want you to design?**

The DriverPass project involved designing a comprehensive, web-based system for a new driver training company. The client, DriverPass, wanted a system that would serve as the central hub for their entire business operation. Their goal was to provide a superior training experience for student drivers to help them pass their DMV tests. The system needed to support multiple user roles and provide a customer-facing website for students to register for an account, purchase training packages, and schedule their on-the-road driving lessons. It also required a back-end administrative interface for staff to manage user accounts, oversee the appointment calendar, and generate business reports.

#### **What did you do particularly well?**

I believe I did particularly well in translating the client's conversational needs from the interview transcript into structured, formal requirements and visual models. Moving from the initial Business Requirements Document in Project One to the detailed System Design Document in Project Two, I was able to create a clear and logical set of UML diagrams (Use Case, Activity, Sequence, and Class) that accurately represented the client's vision. I was also proud of the client presentation, where I successfully distilled these complex technical diagrams into a simple, non-technical narrative that a business owner could easily understand and approve.

#### **If you could choose one part of your work on these documents to revise, what would you pick? How would you improve it?**

If I could revise one part of my work, I would go back to the initial Business Requirements Document from Project One and expand the nonfunctional requirements section with more specificity. My initial pass was good, but the feedback I received highlighted that I could have been more detailed about things like which specific web browsers to support, what database technology to use, and how to handle specific security threats like brute-force attacks. In Project Two, I made sure to create a much more detailed "Technical Requirements" section to address this, but improving that initial document would have created an even stronger foundation from the very beginning.

#### **How did you interpret the user's needs and implement them into your system design? Why is it so important to consider the user's needs when designing?**

I interpreted the user's needs by carefully dissecting the interview transcript and categorizing each request as either a functional or nonfunctional requirement. For example, when the owner said, "I need to make sure I know who made a reservation," I translated that into a functional requirement: "The system shall track and log all modifications to appointments." When the IT officer mentioned needing to "block their access," I implemented that through a `User` class in the class diagram and a "Manage User Accounts" use case for the IT Officer.

Considering the user's needs is the single most important aspect of system design. If you don't build what the user actually needs, the project is a failure, no matter how technically brilliant the solution is. The entire purpose of systems analysis is to act as a bridge between the business problem and the technical solution, and that can only happen if you are laser-focused on solving the user's real-world challenges.

#### **How do you approach designing software? What techniques or strategies would you use in the future to analyze and design a system?**

My approach to designing software, refined through this course, is to move from the general to the specific. I start with a high-level understanding of the business goals (the "why"), then capture detailed user requirements (the "what"), and only then move on to creating the technical blueprint (the "how").

In the future, I will continue to use the powerful combination of UML diagrams to model a system from multiple perspectives. The Use Case diagram is an invaluable tool for defining scope and agreeing with the client on what will be built. Activity diagrams are perfect for mapping out complex workflows, and Sequence diagrams are essential for developers to understand object interactions. Finally, the Class diagram provides the static data structure that underpins everything. Using these modeling techniques in concert ensures that all stakeholders have a clear, shared understanding of the system before development begins, which is the best strategy to ensure a project's success.
