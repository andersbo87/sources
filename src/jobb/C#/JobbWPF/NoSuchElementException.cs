using System;
using System.Runtime.Serialization;

namespace JobbWPF
{
    [Serializable]
    internal class NoSuchElementException : Exception
    {
        private string message;
        private string elementName;
        Exception innerException;

        /// <summary>
        /// A custom exception to be thrown when trying to access a non-existing element in an array list.
        /// </summary>
        public NoSuchElementException()
        {
        }

        /// <summary>
        /// A custom exception to be thrown when trying to access a non-existing element in an array list.
        /// <param name="message">The message that describes the error.</param>
        /// </summary>
        public NoSuchElementException(string message) : base(message)
        {
            this.message = message;
        }

        /// <summary>
        /// A custom exception to be thrown when trying to access a non-existing element in an array list.
        /// <param name="message">The message that describes the error.</param>
        /// <param name="elementName">The name of the element that caused the current exception.</param>
        /// </summary>
        public NoSuchElementException(string message, string elementName)
        {
            this.message = message;
            this.elementName = elementName;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        /// <param name="innerException">innerException: The exception that is the cause of the current exception, or a null reference (Nothing in Visual Basic) if no inner exception is specified.</param>
        public NoSuchElementException(string message, Exception innerException) : base(message, innerException)
        {
            this.message = message;
            this.innerException = innerException;
        }

        /// <summary>
        /// A custom exception to be thrown when trying to access a non-existing element in an array list.
        /// </summary>
        protected NoSuchElementException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}