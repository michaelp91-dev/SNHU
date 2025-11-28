import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Test class for Contact.java.
 * <p>
 * This class verifies that all requirements for the Contact class are met,
 * including all validation logic for field length, null checks, and format.
 * Each requirement from the milestone prompt is tested, especially the
 * failure conditions ("sad paths").
 */
class ContactTest {

    // --- Requirement 1: Contact ID Tests ---

    @Test
    @DisplayName("Contact creation succeeds with valid data")
    void testContactCreationSuccess() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertNotNull(contact);
        assertEquals("12345", contact.getContactId());
        assertEquals("John", contact.getFirstName());
    }

    @Test
    @DisplayName("Contact ID cannot be longer than 10 characters")
    void testContactIdTooLong() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345678901", "John", "Doe", "1234567890", "123 Main St");
        });
    }

    @Test
    @DisplayName("Contact ID cannot be null")
    void testContactIdNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, "John", "Doe", "1234567890", "123 Main St");
        });
    }

    // Note: The "not updatable" requirement for contactId is enforced by
    // setting the field to 'final' and not providing a 'setContactId' method.
    // This is a compile-time check, not a runtime test.

    // --- Requirement 2: First Name Tests ---

    @Test
    @DisplayName("First Name cannot be longer than 10 characters")
    void testFirstNameTooLong() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "Johnathan11", "Doe", "1234567890", "123 Main St");
        });
    }

    @Test
    @DisplayName("First Name cannot be null")
    void testFirstNameNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", null, "Doe", "1234567890", "123 Main St");
        });
    }

    // --- Requirement 3: Last Name Tests ---

    @Test
    @DisplayName("Last Name cannot be longer than 10 characters")
    void testLastNameTooLong() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", "Doeringer11", "1234567890", "123 Main St");
        });
    }

    @Test
    @DisplayName("Last Name cannot be null")
    void testLastNameNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", null, "1234567890", "123 Main St");
        });
    }

    // --- Requirement 4: Phone Tests ---

    @Test
    @DisplayName("Phone must be exactly 10 digits")
    void testPhoneNot10Digits() {
        // Test too short
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", "Doe", "123456789", "123 Main St");
        });
        // Test too long
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", "Doe", "12345678901", "123 Main St");
        });
    }

    @Test
    @DisplayName("Phone cannot be null")
    void testPhoneNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", "Doe", null, "123 Main St");
        });
    }

    @Test
    @DisplayName("Phone must contain only digits")
    void testPhoneContainsNonDigits() {
        assertThrows(IllegalArgumentException.class, () -> {
            // Contains a letter
            new Contact("12345", "John", "Doe", "123456789A", "123 Main St");
        });
        assertThrows(IllegalArgumentException.class, () -> {
            // Contains a dash
            new Contact("12345", "John", "Doe", "123-456-7890", "123 Main St");
        });
    }

    // --- Requirement 5: Address Tests ---

    @Test
    @DisplayName("Address cannot be longer than 30 characters")
    void testAddressTooLong() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", "Doe", "1234567890", "12345 This Address is Way Too Long 0123");
        });
    }

    @Test
    @DisplayName("Address cannot be null")
    void testAddressNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345", "John", "Doe", "1234567890", null);
        });
    }

    // --- Setter Validation Tests ---

    @Test
    @DisplayName("Setters correctly validate new first name")
    void testSetFirstNameValidation() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertThrows(IllegalArgumentException.class, () -> contact.setFirstName(null), "Setter should block null");
        assertThrows(IllegalArgumentException.class, () -> contact.setFirstName("Johnathan11"), "Setter should block long name");
        assertDoesNotThrow(() -> contact.setFirstName("Jon"), "Setter should allow valid name");
        assertEquals("Jon", contact.getFirstName(), "First name should be updated");
    }
    
    @Test
    @DisplayName("Setters correctly validate new last name")
    void testSetLastNameValidation() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertThrows(IllegalArgumentException.class, () -> contact.setLastName(null), "Setter should block null");
        assertThrows(IllegalArgumentException.class, () -> contact.setLastName("Doeringer11"), "Setter should block long name");
        assertDoesNotThrow(() -> contact.setLastName("Don"), "Setter should allow valid name");
        assertEquals("Don", contact.getLastName(), "Last name should be updated");
    }

    @Test
    @DisplayName("Setters correctly validate new phone")
    void testSetPhoneValidation() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertThrows(IllegalArgumentException.class, () -> contact.setPhone(null), "Setter should block null");
        assertThrows(IllegalArgumentException.class, () -> contact.setPhone("123"), "Setter should block short phone");
        assertThrows(IllegalArgumentException.class, () -> contact.setPhone("123456789A"), "Setter should block non-digits");
        assertDoesNotThrow(() -> contact.setPhone("0987654321"), "Setter should allow valid phone");
        assertEquals("0987654321", contact.getPhone(), "Phone should be updated");
    }

    @Test
    @DisplayName("Setters correctly validate new address")
    void testSetAddressValidation() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertThrows(IllegalArgumentException.class, () -> contact.setAddress(null), "Setter should block null");
        assertThrows(IllegalArgumentException.class, () -> contact.setAddress("12345 This Address is Way Too Long 0123"), "Setter should block long address");
        assertDoesNotThrow(() -> contact.setAddress("456 Side St"), "Setter should allow valid address");
        assertEquals("456 Side St", contact.getAddress(), "Address should be updated");
    }
}