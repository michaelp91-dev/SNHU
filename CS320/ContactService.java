import java.util.HashMap;
import java.util.Map;

/**
 * Manages a collection of Contact objects in memory.
 * <p>
 * This service provides methods to add, delete, and update contacts,
 * enforcing business-level rules such as the uniqueness of contact IDs.
 * <p>
 * Requirements:
 * 1. Use in-memory data structures.
 * 2. Add contacts with a unique ID.
 * 3. Delete contacts per contact ID.
 * 4. Update contact fields (firstName, lastName, Number, Address) per contact ID.
 */
public class ContactService {

    // Using a HashMap provides fast O(1) average-case time complexity
    // for add, delete, and update operations by contactId.
    private final Map<String, Contact> contacts;

    /**
     * Constructs a new ContactService with an empty contact list.
     */
    public ContactService() {
        this.contacts = new HashMap<>();
    }

    /**
     * Adds a new contact to the service.
     * Per requirements, the contact ID must be unique.
     *
     * @param contact The contact to add. Must not be null and must have a valid ID.
     * @return true if the contact was added successfully.
     * @throws IllegalArgumentException if the contact is null, contactId is null,
     * or if the contactId already exists in the service.
     */
    public boolean addContact(Contact contact) {
        if (contact == null || contact.getContactId() == null) {
            throw new IllegalArgumentException("Contact and Contact ID must not be null.");
        }

        // Enforce the "unique ID" requirement.
        if (contacts.containsKey(contact.getContactId())) {
            throw new IllegalArgumentException("Contact ID already exists.");
        }

        contacts.put(contact.getContactId(), contact);
        return true;
    }

    /**
     * Deletes a contact from the service based on the contact ID.
     *
     * @param contactId The ID of the contact to delete.
     * @return true if a contact was found and deleted, false if no contact was found.
     */
    public boolean deleteContact(String contactId) {
        if (contactId == null) {
            return false;
        }
        
        // HashMap.remove() returns the removed object, or null if the key didn't exist.
        return contacts.remove(contactId) != null;
    }

    /**
     * Updates an existing contact's updatable fields.
     * The contact is identified by the contactId.
     *
     * @param contactId  The ID of the contact to update.
     * @param firstName  The new first name.
     * @param lastName   The new last name.
     * @param phone      The new phone number.
     * @param address    The new address.
     * @return true if the contact was found and updated, false if not found.
     * @throws IllegalArgumentException if any of the new field values violate
     * the Contact class's validation rules.
     */
    public boolean updateContact(String contactId, String firstName, String lastName, String phone, String address) {
        if (contactId == null) {
            return false;
        }

        // Retrieve the existing contact
        Contact contactToUpdate = contacts.get(contactId);

        if (contactToUpdate != null) {
            // Delegate validation logic to the Contact object's setters.
            // This follows best practices (DRY, Single Responsibility Principle).
            // The setters will throw an IllegalArgumentException if any rule is broken.
            contactToUpdate.setFirstName(firstName);
            contactToUpdate.setLastName(lastName);
            contactToUpdate.setPhone(phone);
            contactToUpdate.setAddress(address);
            return true;
        }
        
        // Contact with the given ID was not found.
        return false;
    }

    /**
     * Retrieves a contact by its ID.
     * This is a helper method, primarily for testing purposes.
     *
     * @param contactId The ID of the contact to retrieve.
     * @return The Contact object, or null if not found.
     */
    public Contact getContact(String contactId) {
        return contacts.get(contactId);
    }
}