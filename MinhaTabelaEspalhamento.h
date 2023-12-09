#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente
#include <cmath>
#include <string>

template<typename T, std::size_t capac>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, capac>
{
    public:

    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    virtual std::size_t capacidade() const{
        return capac; 
    };

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */
    virtual void inserir(T dado){

        if(contem(dado)) return;

        std::size_t index = funcaoEspalhamento(dado);

        this->tabela[index].inserirNoFim(dado);
    };

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     * 
     * @param dado O dado a ser removido.
     */
    virtual void remover(T dado){

        if(!contem(dado)) throw ExcecaoDadoInexistente();

        std::size_t index = funcaoEspalhamento(dado);

        this->tabela[index].remover(dado);
    };

    /**
     * @brief Verifica se \p dado está contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela{
     * } false caso contrário.
     */
    virtual bool contem(T dado) const{

        return (this->tabela[funcaoEspalhamento(dado)].contem(dado)) ? true : false;
        
    };

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t quantidade() const{
        size_t quantidade = 0;

        for (size_t i = 0; i < capac; i++)
        {
            quantidade += this->tabela[i].tamanho();
        }

        return quantidade;
        
    };
    
    protected:

    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    virtual std::size_t funcaoEspalhamento(T dado) const{
        return codigoEspalhamento(dado) % capac;
    };
    
    private:
        /**
         * @brief Calcula a representação numérica de um tipo integral.
         * 
         * @tparam U O tipo integral.
         * @param integral Um valor integral.
         * @return Um inteiro calculado através de static_cast<std::size_t>(integral)
         */
        template<typename U>
        std::size_t codigoEspalhamento(U integral) const
        {
            return static_cast<std::size_t>(integral);
        }
        
    
        /**
         * @brief Calcula a representação numérica de um string.
         * 
         * @param s um string.
         * @return Um inteiro calculado conforme s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1].
         */
        std::size_t codigoEspalhamento(std::string const& string) const
        {
            size_t sum = 0;

            for (size_t i = 0; i < string.size(); i++)
            {
                sum += string[i]*pow(31, string.size() - i+1);
            }

            return sum;
            
        }
    };

#endif
