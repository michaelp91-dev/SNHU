# InventoryApp

CS-360 Project Three portfolio artifact. This Android app lets warehouse staff sign in, manage stock in a persistent SQLite database, and optionally receive SMS alerts when an item reaches a quantity of zero.

**Artifact:** `MichaelPuckett_InventoryApp.zip` (completed app code design, including the Project Two UI used as the baseline for Project Three)

Optional: `MichaelPuckett_Inventory_LaunchPlan.docx`

**Test login:** username `test` / password `test`

---

## Reflection

### Briefly summarize the requirements and goals of the app you developed. What user needs was this app designed to address?

InventoryApp is a warehouse stock tracker. The goal was to build a fully functional Android app that warehouse managers, inventory clerks, and business owners can use to keep item counts accurate during a shift. Users needed a way to create an account, sign in, see every item in one place, add or remove items, change quantities, and get a warning when stock runs out. The app had to keep that data after it is closed, and SMS alerts had to stay optional so the rest of the app still works if the user denies permission.

### What screens and features were necessary to support user needs and produce a user-centered UI for the app? How did your UI designs keep users in mind? Why were your designs successful?

Three screens support those needs: a login screen, an SMS permission screen, and an inventory grid. Login has username, password, Login, and Create Account so first-time users and returning users can both get in quickly. The permission screen asks about SMS before the inventory opens, with a clear Allow SMS path and a Continue without SMS path. The inventory screen shows item names and quantities in a grid, with + and − to update counts, Delete to remove a row, and a floating add button. The UI stays simple because warehouse work is busy. Labels are plain, the main actions are large buttons, and low-stock rows are highlighted in red. That design is successful because a clerk can add, update, or delete an item in a few taps without leaving the grid.

### How did you approach the process of coding your app? What techniques or strategies did you use? How could those techniques or strategies be applied in the future?

I started from the Project Two layouts and wired Java behind the existing screen IDs instead of rebuilding the UI from scratch. I split the work into small classes: a SQLite helper for the database, an adapter for the grid, a helper for SMS, and one activity per screen. I used in-line comments, consistent names, and string resources so the code stays readable. I also tested each feature in the emulator before moving to the next one, which made bugs easier to find. In a later project I would use the same approach: keep the UI stable, put data access in its own class, and add one feature at a time so login, storage, and notifications do not get mixed together.

### How did you test to ensure your code was functional? Why is this process important, and what did it reveal?

I compiled the project in Android Studio and used the emulator to walk through the real user paths. I created an account, logged in with a saved username and password, added items, changed quantities, deleted items, closed the app, and opened it again to confirm the database was still there. I tested SMS twice: once by granting SEND_SMS and lowering an item to zero, and once by skipping or denying permission and confirming the grid still worked. That process matters because a screen can look finished and still fail when the database or a permission is involved. Testing showed that the original item row layout needed real constraints, that a phone number was required before an SMS could be sent, and that adaptive icons had to live in a v26 resource folder because the app supports Android 7.0.

### Consider the full app design and development process from initial planning to finalization. Where did you have to innovate to overcome a challenge?

The hardest stretch was turning a UI-only prototype into working, persistent code without breaking the original screens. The Project Two item row used editor-only positions, so it would not line up as a real grid. I rebuilt that row as a constrained table layout with update buttons while keeping the same screen flow. Another challenge was SMS. Newer Android versions require a runtime prompt, and sending a text can fail on a tablet or an emulator with no radio. I treated SMS as an add-on: the inventory still saves if permission is denied or if the send fails. That let the app meet the notification requirement without making SMS a single point of failure.

### In what specific component of your mobile app were you particularly successful in demonstrating your knowledge, skills, and experience?

The SQLite layer is the strongest piece. The users table stores logins that never appear in the grid, and the inventory table stores the rows that do. Create, read, update, and delete all go through the same helper, and each account only sees its own items. That shows I can connect a user-centered UI to a persistent database, keep classes focused, and still leave room for an optional feature like SMS. Those are the skills I would point to first in a portfolio review.
