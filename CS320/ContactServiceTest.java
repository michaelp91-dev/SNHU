import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Test class for ContactService.java.
 * <p>
 * This class verifies that all requirements for the ContactService class are met.
 * It tests the ability to add, delete, and update contacts, and ensures
 * business rules (like unique IDs) are enforced.
 */
class ContactServiceTest {

    private ContactService service;
    private Contact contact1;
    private String validId;
    private String validFirstName;
    private String validLastName;
    private String validPhone;
    private String validAddress;

    /**
     * Sets up a new ContactService and a default valid Contact
     * before each test method is executed. This ensures test isolation.
     */
    @BeforeEach
    void setUp() {
        service = new ContactService();
        validId = "12345";
        validFirstName = "Jane";
        validLastName = "Doe";
        validPhone = "0987654321";
        validAddress = "100 Main St";
        contact1 = new Contact(validId, validFirstName, validLastName, validPhone, validAddress);
    }

    // --- Requirement 1: Add Contact Tests ---

    @Test
    @DisplayName("Successfully add a new contact")
    void testAddContactSuccess() {
        assertTrue(service.addContact(contact1));
        
        // Verify the contact was actually added and is correct
        Contact retrievedContact = service.getContact(validId);
        assertNotNull(retrievedContact);
        assertEquals(validFirstName, retrievedContact.getFirstName());
    }

    @Test
    @DisplayName("Fail to add a contact with a duplicate ID")
    void testAddContactDuplicateId() {
        service.addContact(contact1); // Add the contact first

        // Create a new contact object with the *same* ID
        Contact contact2 = new Contact(validId, "John", "Smith", "1112223333", "200 Side St");

        // Verify that adding the second contact throws an exception
        assertThrows(IllegalArgumentException.class, () -> {
            service.addContact(contact2);
        });
    }

    @Test
    @DisplayName("Fail to add a null contact")
    void testAddContactNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            service.addContact(null);
        });
    }


    // --- Requirement 2: Delete Contact Tests ---

    @Test
    @DisplayName("Successfully delete an existing contact")
    void testDeleteContactSuccess() {
        service.addContact(contact1);
        assertNotNull(service.getContact(validId), "Contact should be present before delete");

        assertTrue(service.deleteContact(validId));
        assertNull(service.getContact(validId), "Contact should be null after delete");
    }

    @Test
    @DisplayName("Fail to delete a non-existent contact")
    void testDeleteContactNotFound() {
        service.addContact(contact1); // Add a different contact
        
        // Try to delete an ID that doesn't exist
        assertFalse(service.deleteContact("54321"));
        
        // Ensure the original contact is unharmed
        assertNotNull(service.getContact(validId));
    }


    // --- Requirement 3: Update Contact Tests ---

    @Test
    @DisplayName("Successfully update an existing contact")
    void testUpdateContactSuccess() {
        service.addContact(contact1);

        String newFirstName = "Janet";
        String newLastName = "Doeman";
        String newPhone = "1112223333";
        String newAddress = "101 Main St";

        assertTrue(service.updateContact(validId, newFirstName, newLastName, newPhone, newAddress));

        // Verify that all fields were updated correctly
        Contact updatedContact = service.getContact(validId);
        assertNotNull(updatedContact);
        assertEquals(newFirstName, updatedContact.getFirstName());
        assertEquals(newLastName, updatedContact.getLastName());
        assertEquals(newPhone, updatedContact.getPhone());
        assertEquals(newAddress, updatedContact.getAddress());
    }

    @Test
    @DisplayName("Fail to update a non-existent contact")
    void testUpdateContactNotFound() {
        service.addContact(contact1);
        
        // Try to update an ID that doesn't exist
        assertFalse(service.updateContact("54321", "New", "Name", "0000000000", "New Address"));
    }

    @Test
    @DisplayName("Fail to update a contact with invalid field data")
    void testUpdateContactFailsValidation() {
        service.addContact(contact1);
        
        // Try to update with an invalid first name (too long)
        assertThrows(IllegalArgumentException.class, () -> {
            service.updateContact(validId, "ThisNameIsWayTooLong", "Doe", "0987654321", "100 Main St");
        });

        // Try to update with an invalid phone number (not 10 digits)
        assertThrows(IllegalArgumentException.class, () -> {
            service.updateContact(validId, "Jane", "Doe", "123", "100 Main St");
        });

        // Try to update with a null address
        assertThrows(IllegalArgumentException.class, () -> {
            service.updateContact(validId, "Jane", "Doe", "0987654321", null);
        });

        // Verify that the original contact data was not corrupted
        Contact originalContact = service.getContact(validId);
        assertEquals(validFirstName, originalContact.getFirstName());
        assertEquals(validLastName, originalContact.getLastName());
    }
}