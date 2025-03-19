/*
 * Decompiled with CFR 0.152.
 */
import java.awt.Component;
import javax.swing.DefaultListModel;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;

class TopDestinationListFrame
extends JFrame {
    private DefaultListModel listModel;

    public TopDestinationListFrame() {
        super("Top Five Destination List");
        this.setDefaultCloseOperation(3);
        this.setSize(900, 750);
        this.listModel = new DefaultListModel();
        this.addDestinationNameAndPicture("1. Top Destination (short sentence description)", new ImageIcon(this.getClass().getResource("/resources/TestImage.jpg")));
        this.addDestinationNameAndPicture("2. 2nd Top Destination", new ImageIcon(this.getClass().getResource("/resources/TestImage.jpg")));
        this.addDestinationNameAndPicture("3. 3rd Top Destination", new ImageIcon(this.getClass().getResource("/resources/TestImage.jpg")));
        this.addDestinationNameAndPicture("4. 4th Top Destination", new ImageIcon(this.getClass().getResource("/resources/TestImage.jpg")));
        this.addDestinationNameAndPicture("5. 5th Top Destination", new ImageIcon(this.getClass().getResource("/resources/TestImage.jpg")));
        JList list = new JList(this.listModel);
        JScrollPane scrollPane = new JScrollPane(list);
        TextAndIconListCellRenderer renderer = new TextAndIconListCellRenderer(2);
        list.setCellRenderer(renderer);
        this.getContentPane().add((Component)scrollPane, "Center");
    }

    private void addDestinationNameAndPicture(String text, Icon icon) {
        TextAndIcon tai = new TextAndIcon(text, icon);
        this.listModel.addElement(tai);
    }
}
