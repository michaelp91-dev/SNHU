/**
 * Represents a contact with personal information.
 * <p>
 * This class is designed to be a "model" or "data object" that enforces all
 * field-level validation rules upon creation and modification.
 * <p>
 * Requirements:
 * 1. Contact ID: (Required) String, unique, <= 10 chars, not null, not updatable.
 * 2. firstName: (Required) String, <= 10 chars, not null.
 * 3. lastName: (Required) String, <= 10 chars, not null.
 * 4. phone: (Required) String, exactly 10 digits, not null.
 * 5. address: (Required) String, <= 30 chars, not null.
 */
public class Contact {

    // 'final' ensures the contactId is not updatable, fulfilling requirement 1.
    private final String contactId;
    private String firstName;
    private String lastName;
    private String phone;
    private String address;

    /**
     * Constructs a new Contact object, validating all fields.
     *
     * @param contactId A unique ID for the contact (max 10 chars, not null).
     * @param firstName The contact's first name (max 10 chars, not null).
     * @param lastName  The contact's last name (max 10 chars, not null).
     * @param phone     The contact's phone number (exactly 10 digits, not null).
     * @param address   The contact's address (max 30 chars, not null).
     * @throws IllegalArgumentException if any validation rule is violated.
     */
    public Contact(String contactId, String firstName, String lastName, String phone, String address) {
        // Use private validation helpers to check rules and throw exceptions
        validateField(contactId, 10, "Contact ID");
        validateField(firstName, 10, "First Name");
        validateField(lastName, 10, "Last Name");
        validatePhone(phone);
        validateField(address, 30, "Address");

        // If all validation passes, assign the fields
        this.contactId = contactId;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phone = phone;
        this.address = address;
    }

    // --- Validation Helpers ---

    /**
     * A generic helper to validate a string field for null and length.
     *
     * @param field     The string value to check.
     * @param maxLength The maximum allowed length.
     * @param fieldName The name of the field (for error messages).
     * @throws IllegalArgumentException if the field is null or exceeds maxLength.
     */
    private void validateField(String field, int maxLength, String fieldName) {
        if (field == null) {
            throw new IllegalArgumentException(fieldName + " must not be null.");
        }
        if (field.length() > maxLength) {
            throw new IllegalArgumentException(fieldName + " cannot be longer than " + maxLength + " characters.");
        }
    }

    /**
     * A specific helper to validate the phone number requirement.
     *
     * @param phone The phone number string to check.
     * @throws IllegalArgumentException if the phone is null, not 10 chars, or contains non-digits.
     */
    private void validatePhone(String phone) {
        if (phone == null) {
            throw new IllegalArgumentException("Phone must not be null.");
        }
        // Use a regular expression to ensure it's exactly 10 digits.
        if (!phone.matches("\\d{10}")) {
            throw new IllegalArgumentException("Phone must be exactly 10 digits.");
        }
    }

    // --- Getters ---

    public String getContactId() {
        return contactId;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getPhone() {
        return phone;
    }

    public String getAddress() {
        return address;
    }

    // --- Setters for Updatable Fields ---
    // Note: No setter for contactId, as it's final and not updatable.

    public void setFirstName(String firstName) {
        validateField(firstName, 10, "First Name");
        this.firstName = firstName;
    }

    public void setLastName(String lastName) {
        validateField(lastName, 10, "Last Name");
        this.lastName = lastName;
    }

    public void setPhone(String phone) {
        validatePhone(phone);
        this.phone = phone;
    }

    public void setAddress(String address) {
        validateField(address, 30, "Address");
        this.address = address;
    }
}