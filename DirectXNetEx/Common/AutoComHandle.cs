using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DirectXNet.Common
{
    /// <summary>
    /// Wrapper for all COM objects to dispose them when not needed.
    /// Use this class only for fields.
    /// </summary>
    /// <typeparam name="T">Type of COM object.</typeparam>
    public class AutoComHandle<T> where T : Unknown
    {
        private T handle;

        private bool Valid()
        {
            return handle != null;
        }

        /// <summary>
        /// Creates the empty handle.
        /// </summary>
        public AutoComHandle()
        {
            handle = null;
        }

        /// <summary>
        /// Creates the handle and assign the object.
        /// </summary>
        /// <param name="obj">Object to assign.</param>
        public AutoComHandle(T obj)
        {
            handle = obj;
        }

        /// <summary>
        /// Creates the handle from other handle.
        /// </summary>
        /// <param name="other">Other handle to assign. The object assigned to other handle
        /// will be released.</param>
        public AutoComHandle(AutoComHandle<T> other)
        {
            handle = other.Release();
        }

        /// <summary>
        /// Gets the object in the handle.
        /// </summary>
        /// <returns>Object in the handle.</returns>
        /// <remarks>Do not dispose the object from this method.</remarks>
        public T Get()
        {
            return handle;
        }

        /// <summary>
        /// Checks whether the handle is valid(not null).
        /// </summary>
        /// <param name="obj">Handle to check.</param>
        public static implicit operator bool(AutoComHandle<T> obj)
        {
            return obj.Valid();
        }

        /// <summary>
        /// Checks whether the handle is not valid(null).
        /// </summary>
        /// <param name="obj">Handle to check.</param>
        /// <returns><see langword="true"/> if not valid. Else, <see langword="false"/>.</returns>
        public static bool operator!(AutoComHandle<T> obj)
        {
            return !obj.Valid();
        }

        /// <summary>
        /// Dispose the object in the handle and assign new object.
        /// </summary>
        /// <param name="newObj">Object to assign.</param>
        public void Reset(T newObj)
        {
            if (handle != newObj)
            {
                if (Valid())
                    handle.Dispose();

                handle = newObj;
            }
        }

        /// <summary>
        /// Dispose the object in the handle and assign null.
        /// </summary>
        public void Reset()
        {
            Reset(null);
        }

        /// <summary>
        /// Gets the object in the handle and assign null.
        /// </summary>
        /// <returns>Object in the handle.</returns>
        /// <remarks>This method does not dispose the object.</remarks>
        public T Release()
        {
            T tmp = handle;
            handle = null;
            return tmp;
        }
    }
}
