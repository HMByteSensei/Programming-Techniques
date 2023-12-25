package ba.unsa.etf.rpr.lab6.kalkulator;

import javafx.event.ActionEvent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

public class HelloController {
    public TextField txt_result;
    private Double broj1;
    private Double broj2;
    private String op = "";
    private boolean daLiSeMozeIzabratiTacka = true;

    public void number(ActionEvent actionEvent) {
        Button kliknutoDugme = (Button)actionEvent.getSource();
        String tekstDugmeta = (String)kliknutoDugme.getText();
        if(tekstDugmeta.equals(".")) {
            if(!daLiSeMozeIzabratiTacka) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Tacka izabrana vise puta");
                alert.setHeaderText("Nije dozvoljeno unositi tacku vise puta");
                alert.setContentText("Ponovno unesite broj");
                alert.showAndWait();
                txt_result.setText("");
                daLiSeMozeIzabratiTacka = true;
                return;
            }
            daLiSeMozeIzabratiTacka = false;
        }
        txt_result.setText(txt_result.getText() + tekstDugmeta);
    }

    public void operation(ActionEvent actionEvent) {
        String operacija = ((Button)actionEvent.getSource()).getText();
        if(!operacija.equals("=")) {
            if(!op.equals("")) {
                return;
            }
            op = operacija;
            broj1 = Double.parseDouble(txt_result.getText());
            txt_result.setText("");
        } else {
            if(broj1 == null || op.equals("")) {
                return;
            }
            broj2 = Double.parseDouble(txt_result.getText());
            txt_result.setText("");
            calculate();
        }
    }

    public void calculate() {
        System.out.println("Broj1: " + broj1);
        System.out.println("Broj2: " + broj2);
        System.out.println("Op: " + op);

        Double rezultat = 0.;
        switch(op) {
            case "%":
                rezultat = broj1 % broj2;
                break;
            case "/":
                if(broj2 == 0.) {
                    throw new IllegalArgumentException("Dijeljenje s nulom");
                } else {
                    rezultat = broj1 / broj2;
                }
                break;
            case "*":
                rezultat = broj1 * broj2;
                break;
            case "-":
                rezultat = broj1 - broj2;
                break;
            case "+":
                rezultat = broj1 + broj2;
                break;
            default: return;
        }
        txt_result.setText(rezultat.toString());
        op = "";
    }
}