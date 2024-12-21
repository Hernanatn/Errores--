#pragma once

#include <string>

namespace Error {
    enum CodigoEstado
    {
        FATAL = -2,
        ERROR = -1,
        EXITO = 0,
    };

    /**
     * @brief Tipo que representa un error con un código y un mensaje descriptivo.
     *
     * Este tipo se utiliza para encapsular un error mediante un código de estado
     * y un mensaje de error asociado. Los códigos de estado se definen mediante el
     * `enum CodigoEstado`, donde `ERROR` representa un estado de error y `EXITO` indica
     * una operación exitosa.
     *
     * El tipo proporciona mecanismos para obtener el código de estado, el mensaje
     * asociado, y también permite modificar el mensaje mediante la función `agregarMensaje`.
     * Además, sobrecarga varios operadores para permitir el uso conveniente del tipo en
     * expresiones booleanas y de conversión a tipos como `std::string` o `const char*`.
     *
     * @note El operador `<<` permite imprimir un objeto del tipo `Error` utilizando
     * flujos de salida estándar como `std::cout`.
     */
    struct Error{
        private:
        CodigoEstado codigo;
        std::string mensaje;
        public:
        Error() noexcept : Error{CodigoEstado::ERROR, "ERROR"} {};
        explicit Error(CodigoEstado codigo, std::string mensaje = "ERROR");
        explicit Error(Error *e); // <HACER/>
        CodigoEstado Codigo();
        std::string Mensaje();

        void agregarMensaje(std::string mensaje);

        operator bool();
        operator std::string() const;
        operator const char*() const;
        operator char*();

    
        // Sobrecarga del operador << para hacer que Error sea "imprimible" con cualquier "output stream", e.g., std::cout.
        friend std::ostream &operator<<(std::ostream &os, Error const &e){
            return os << e.mensaje;
        }
    };

    Error Exito();
    Error Fatal();
    Error Generico();

        Error::Error(Error *e){/* <HACER/> */};

    Error::Error(CodigoEstado codigo, std::string mensaje){
        this->codigo = codigo;
        this->mensaje = "[" + std::to_string(codigo) + "] " + mensaje + "\n";
    };
    void Error::agregarMensaje(std::string mensaje){
        this->mensaje = this->mensaje.append(mensaje);
    };

    std::string Error::Mensaje(){
        return mensaje;
    };
    CodigoEstado Error::Codigo(){
        return codigo;
    };

    Error::operator bool(){ return (this->codigo != CodigoEstado::EXITO); };

    Error::operator std::string() const  { return mensaje ;}
    Error::operator const char*() const  { return mensaje.c_str() ;}
    Error::operator char*() { return const_cast<char*>(mensaje.c_str()) ;}

    Error Exito(std::string mensaje ="Exito"){
        return Error(
            CodigoEstado::EXITO,
            mensaje
        );
    }
    Error Fatal(std::string mensaje ="Error Fatal"){
        return Error(
            CodigoEstado::FATAL,
            mensaje
        );
    }
    Error Generico(std::string mensaje ="Error"){
        return Error(
            CodigoEstado::ERROR,
            mensaje
        );
    }

}