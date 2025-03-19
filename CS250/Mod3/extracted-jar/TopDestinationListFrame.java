import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import javax.swing.DefaultListModel;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame; //Import JLabel
import javax.swing.JLabel; //Import BorderLayout
import javax.swing.JList; //Import SwingConstants
import javax.swing.JScrollPane; //Import Font
import javax.swing.SwingConstants; //Import Color

class TopDestinationListFrame
extends JFrame {
    private DefaultListModel listModel;

    public TopDestinationListFrame() {
        super("Top Five Destination List");
        this.setDefaultCloseOperation(3);
        this.setSize(900, 750);
        this.listModel = new DefaultListModel();

        // Add your top five destinations here
        addDestinationNameAndPicture("Paris, France - The City of Lights", new ImageIcon(this.getClass().getResource("/resources/image.png")));
        addDestinationNameAndPicture("Rome, Italy - Ancient ruins and pasta", new ImageIcon(this.getClass().getResource("/resources/image(1).png")));
        addDestinationNameAndPicture("Tokyo, Japan - Modern and traditional", new ImageIcon(this.getClass().getResource("/resources/image(2).png")));
        addDestinationNameAndPicture("New York City, USA - The Big Apple", new ImageIcon(this.getClass().getResource("/resources/image(3).png")));
        addDestinationNameAndPicture("Machu Picchu, Peru - Incan citadel", new ImageIcon(this.getClass().getResource("/resources/image(4).png")));

        JList list = new JList(this.listModel);
        JScrollPane scrollPane = new JScrollPane(list);
        TextAndIconListCellRenderer renderer = new TextAndIconListCellRenderer(2);
        list.setCellRenderer(renderer);
        this.getContentPane().add((Component)scrollPane, "Center");

        // Add name label
        JLabel nameLabel = new JLabel("Your Name Here", SwingConstants.CENTER); // Replace with your name
        nameLabel.setFont(new Font("Arial", Font.BOLD, 16));
        nameLabel.setForeground(Color.BLUE);
        this.getContentPane().add(nameLabel, BorderLayout.SOUTH); //Add the name label to the bottom of the screen.
    }

    private void addDestinationNameAndPicture(String text, Icon icon) {
        TextAndIcon tai = new TextAndIcon(text, icon);
        this.listModel.addElement(tai);
    }
}