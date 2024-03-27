package validation;

public class ValidationException extends RuntimeException {
    /**
     * Clasa pentru exceptii
     * @param exception - exceptia pe care o arunca
     */
    public ValidationException(String exception){
        super(exception);
    }
}
