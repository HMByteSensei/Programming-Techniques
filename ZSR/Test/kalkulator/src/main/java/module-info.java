module ba.unsa.etf.rpr.lab6.kalkulator {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens ba.unsa.etf.rpr.lab6.kalkulator to javafx.fxml;
    exports ba.unsa.etf.rpr.lab6.kalkulator;
}