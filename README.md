# Identify-training-needs

This is a CLI application (with not so beautifully designed interface) that can be used in an organization.

The 3 modes: Admin, User and Manager have unique roles. Admin and Manager are unique but users can be multiple.

The role of the admin is to add the courses to the existing courses.txt file at any point of time depending upon the relevance and popularity or trend of that particular course. Redundance is checked for courses and durations.

The role of User is to just request a particular course in the list of available courses to get trained in. The courses.txt file also has duration in months for each course. So the total duration of all courses a particlar user has requested must not go beyond 12 months since its an annual plan.

The role of the Manager is to view the user requests and approve them or not. If not approved, the user request goes to the waiting list where the manager can, at a later point of time, approve them. If not approved in the waiting list, the request is parmanently deleted. The manager also checks for redundancey checks in user requests.

Finally, an annual report is generated which contains the details of all the user requests which have been approved by the manager. 

This is an OOP project. It contains some features like Static variables, Classes, Objects, Friend functions, Constructors, Exception handling, user defined namespaces, structures and file handling.