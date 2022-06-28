
#ifndef __FIFO_H__
#define __FIFO_H__
  //! FIFO Memory Model (Single Byte Mode)
  typedef struct
  {
    char *p_start_addr; //!< FIFO Memory Pool Start Address
    char *p_end_addr;   //!< FIFO Memory Pool End Address
    int free_num;       //!< The remain capacity of FIFO
    int used_num;       //!< The number of elements in FIFO
    char *p_read_addr;  //!< FIFO Data Read Index Pointer
    char *p_write_addr; //!< FIFO Data Write Index Pointer
  } fifo_s_t;


  //******************************************************************************************
  //
  //! \brief  Create An New FIFO Instance(in Single Mode).
  //! This function allocate enought room for N blocks fifo elements, then return the pointer
  //! of FIFO.
  //!
  //! \param  [in] uint_cnt is count of fifo elements.
  //! \retval The Pointer of FIFO instance, return NULL is failure to allocate memory.
  //!
  //! \note   -# You must enable USE_MEMORY_ALLOC macro and ensure your system have <stdlib.h>
  //!            Header file before use this function.
  //! \note   -# Functions FIFO_Create and FIFO_Destory must be used in pairs.
  //!
  //******************************************************************************************
  fifo_s_t *fifo_s_create(int uint_cnt);

  //******************************************************************************************
  //
  //! \brief  Destory FIFO Instance(in Single Mode).
  //!  This function release memory, then reinit the FIFO struct.
  //!
  //! \param  [in] p_fifo is the pointer of FIFO instance
  //! \retval None.
  //!
  //! \note   -# You must enable USE_MEMORY_ALLOC macro and ensure your system have <stdlib.h>
  //!            Header file before use this function.
  //
  //******************************************************************************************
  void fifo_s_destroy(fifo_s_t * p_fifo);

#endif // USE_DYNAMIC_MEMORY

  //******************************************************************************************
  //
  //! \brief  Initialize an static FIFO struct(in single mode).
  //!
  //! \param  [in] p_fifo is the pointer of valid FIFO instance.
  //! \param  [in] p_base_addr is the base address of pre-allocate memory, such as array.
  //! \param  [in] uint_cnt is count of fifo elements.
  //! \retval 0 if initialize successfully, otherwise return -1.
  //
  //******************************************************************************************
  int fifo_s_init(fifo_s_t * p_fifo, void *p_base_addr, int uint_cnt);

  //******************************************************************************************
  //
  //! \brief  Put an element into FIFO(in single mode).
  //!
  //! \param  [in]  p_fifo is the pointer of valid FIFO.
  //! \param  [in]  element is the data element you want to put
  //!
  //! \retval 0 if operate successfully, otherwise return -1.
  //
  //******************************************************************************************
  int fifo_s_put(fifo_s_t * p_fifo, char element);

  int fifo_s_puts(fifo_s_t * p_fifo, char *p_source, int len);
  int fifo_s_puts_noprotect(fifo_s_t * p_fifo, char *p_source, int len);

  //******************************************************************************************
  //
  //! \brief  Get an element from FIFO(in single mode).
  //!
  //! \param  [in]  p_fifo is the pointer of valid FIFO.
  //!
  //! \retval the data element of FIFO.
  //
  //******************************************************************************************
  char fifo_s_get(fifo_s_t * p_fifo);
  int fifo_s_gets(fifo_s_t * p_fifo, char *p_dest, int len);
  int fifo_s_gets_noprotect(fifo_s_t * p_fifo, char *p_dest, int len);

  //******************************************************************************************
  //
  //! \brief  Pre-Read an element from FIFO(in single mode).
  //!
  //! \param  [in]  p_fifo is the pointer of valid FIFO.
  //! \param  [in]  Offset is the offset from current pointer.
  //!
  //! \retval the data element of FIFO.
  //
  //******************************************************************************************
  char fifo_s_preread(fifo_s_t * p_fifo, int offset);
  int fifo_s_prereads(fifo_s_t * p_fifo, char *p_dest, int offset, int len);

  //******************************************************************************************
  //
  //! \brief  FIFO is empty (in single mode)?
  //!
  //! \param  [in] p_fifo is the pointer of valid FIFO.
  //!
  //! \retval - None-zero(true) if empty.
  //!         - Zero(false) if not empty.
  //
  //******************************************************************************************
  char fifo_s_isempty(fifo_s_t * p_fifo);

  //******************************************************************************************
  //
  //! \brief  FIFO is full (in single mode)?
  //!
  //! \param  [in] p_fifo is the pointer of valid FIFO.
  //!
  //! \retval - None-zero(true) if full.
  //!         - Zero(false) if not full.
  //
  //******************************************************************************************
  char fifo_s_isfull(fifo_s_t * p_fifo);

  //******************************************************************************************
  //
  //! \brief  Get FIFO the number of elements(in single mode)?
  //!
  //! \param  [in] p_fifo is the pointer of valid FIFO.
  //!
  //! \retval The number of elements in FIFO.
  //
  //******************************************************************************************
  int fifo_s_used(fifo_s_t * p_fifo);

  //******************************************************************************************
  //
  //! \brief  Get FIFO the number of elements(in single mode)?
  //!
  //! \param  [in] p_fifo is the pointer of valid FIFO.
  //!
  //! \retval The number of elements in FIFO.
  //
  //******************************************************************************************
  int fifo_s_free(fifo_s_t * p_fifo);

  //******************************************************************************************
  //
  //! \brief  Flush the content of FIFO.
  //!
  //! \param  [in] p_fifo is the pointer of valid FIFO.
  //!
  //! \retval 0 if success, -1 if failure.
  //
  //******************************************************************************************
  void fifo_s_flush(fifo_s_t * p_fifo);
  int fifo_s_discard(fifo_s_t * p_fifo, int len);

